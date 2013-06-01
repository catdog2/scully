/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#include "Token.h"

#include "AST/CodeGenVisitor.h"

#include "llvm/DerivedTypes.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/IRBuilder.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/PassManager.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/DataLayout.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/TargetSelect.h"

// this file is auto generated from grammar/grammar.y
#include "grammar.h"

#include "lexertl/generator.hpp"
#include "lexertl/lookup.hpp"
#include "lexertl/rules.hpp"
#include "lexertl/state_machine.hpp"

int main() {
	lexertl::rules rules;
	lexertl::state_machine state_machine;

	//keywords
	rules.add("bool", T_BOOL);
	rules.add("for", T_FOR);
	rules.add("if", T_IF);
	rules.add("int", T_INT);
	rules.add("return", T_RETURN);
	rules.add("void", T_VOID);
	rules.add("rfor", T_RFOR);
	rules.add("rif", T_RIF);
	rules.add("string", T_STRING);

	// special characters
	rules.add("\"(\"", T_LPAREN);
	rules.add("\")\"", T_RPAREN);
	rules.add("mulder", T_BEGIN);
	rules.add("scully", T_END);
	rules.add(",", T_COMMA);
	rules.add(";", T_SEMICOLON);

	// operators
	rules.add("=", T_ASSIGN);
	rules.add("==", T_EQUALS);
	rules.add("<", T_LESS);
	rules.add("\"+\"", T_PLUS);
	rules.add("\"-\"", T_MINUS);
	rules.add("\"*\"", T_TIMES);
	rules.add("\"/\"", T_DIV);

	// constants
	rules.add("true", T_TRUE);
	rules.add("false", T_FALSE);
	rules.add("\\d+", T_CINT);

	// identifier
	rules.add("[a-zA-Z_][a-zA-Z_0-9]*", T_IDENTIFIER);

	// whitespace
	rules.add("\\s+", T_WHITESPACE);

	lexertl::generator::build(rules, state_machine);
	state_machine.minimise();

	std::cout << "The scully programming language v0.2" << std::endl;


	// Setup LLVM JIT
	llvm::InitializeNativeTarget();
	llvm::Module* module = new llvm::Module("SCULLY/JIT", llvm::getGlobalContext());
	std::string errStr;
	llvm::ExecutionEngine* ee = llvm::EngineBuilder(module).setErrorStr(&errStr).create();
	if (!ee) {
		std::cerr << "Error creating Execution Engine: " << errStr << std::endl;
		return 1;
	}

	// Set up the optimizer pipeline. Start with registering info about how the
	// target lays out data structures.
	llvm::FunctionPassManager* fpm = new llvm::FunctionPassManager(module);

	fpm->add(new llvm::DataLayout(*ee->getDataLayout()));
	// Provide basic AliasAnalysis support for GVN.
	fpm->add(llvm::createBasicAliasAnalysisPass());
	// Do simple "peephole" optimizations and bit-twiddling optzns.
	fpm->add(llvm::createInstructionCombiningPass());
	// Reassociate expressions.
	fpm->add(llvm::createReassociatePass());
	// Eliminate Common SubExpressions.
	fpm->add(llvm::createGVNPass());
	// Simplify the control flow graph (deleting unreachable blocks, etc).
	fpm->add(llvm::createCFGSimplificationPass());

	fpm->doInitialization();

	CodeGenVisitor* cv = new CodeGenVisitor(module, fpm);

	void* parser = scullyParserAlloc(malloc);

	while (true) {
		std::cout << "> ";
		std::string input;
		std::getline(std::cin, input);
		if (std::cin.eof()) {
			std::cout << std::endl << "Bye." << std::endl;
			return 0;
		}

		auto iter = input.begin();
		auto end = input.end();
		lexertl::smatch results(iter, end);

		do {
			lexertl::lookup (state_machine, results);
			std::string s(results.start, results.end);
			if (results.id != T_WHITESPACE) {
				std::cout << "Id: " << results.id << ", Token: " << s << std::endl;
				scullyParser(parser, results.id, new Token(s), cv);
			}
		} while (results.id != 0);

		module->dump();
	}

	scullyParserFree(parser, free);
	return 0;
}
