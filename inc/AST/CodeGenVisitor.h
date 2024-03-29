/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#ifndef CODEGENVISITOR_H
#define CODEGENVISITOR_H

#include "ASTVisitor.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/IRBuilder.h"
#include "llvm/Module.h"
#include "llvm/PassManager.h"
#include <map>
#include <string>

class CodeGenVisitor : public ASTVisitor {
public:
	CodeGenVisitor(llvm::Module* module, llvm::FunctionPassManager* fpm, llvm::ExecutionEngine* ee);
	virtual ~CodeGenVisitor();

 	virtual void visit(AssignmentExpression* e);
	virtual void visit(BinOpExpression* e);
	virtual void visit(ConstantExpression* e);
	virtual void visit(ExpressionStatement* e);
	virtual void visit(ForStatement* e);
	virtual void visit(FunctionCallExpression* e);
	virtual void visit(FunctionDefinition* e);
	virtual void visit(IfStatement* e);
	virtual void visit(ParameterList* e);
	virtual void visit(RandomForStatement* e);
	virtual void visit(RandomIfStatement* e);
	virtual void visit(ReturnStatement* e);
	virtual void visit(Scope* e);
	virtual void visit(StatementList* e);
	virtual void visit(ValueList* e);
	virtual void visit(VariableDefinition* e);
	virtual void visit(LoadExpression* e);

	void JIT(Expression* e);
private:
	void putNamedValue(const std::string& name, llvm::Value* value);
	llvm::Value* getNamedValue(const std::string& name);

	llvm::IRBuilder<>* builder_;
	llvm::FunctionPassManager* fpm_;
	llvm::Module* module_;
	llvm::ExecutionEngine* ee_;

	int scope_;
	std::vector<std::map<std::string, llvm::Value*>> namedValues_;
	llvm::Value* value_;
};

#endif // CODEGENVISITOR_H
