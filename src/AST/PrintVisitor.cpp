#include "AST/PrintVisitor.h"
#include <iostream>
#include <sstream>

PrintVisitor::PrintVisitor() : level_(0) {
	//
}

PrintVisitor::~PrintVisitor() {
	//
}

void PrintVisitor::visit(AssignmentExpression* e) {
	println("AssignmentExpression");
	level_++;
	std::stringstream ss;
	ss << e->getId() << " = ";
	println(ss.str());
	e->getExpr()->accept(this);
	level_--;
}

void PrintVisitor::visit(BinOpExpression* e) {
	// TODO implement
}

void PrintVisitor::visit(ConstantExpression* e) {
	// TODO implement
}

void PrintVisitor::visit(ExpressionStatement* e) {
	println("ExpressionStatement");
	level_++;
	// TODO implement
	level_--;
}

void PrintVisitor::visit(ForStatement* e) {
	// TODO implement
}

void PrintVisitor::visit(FunctionCallExpression* e) {
	// TODO implement
}

void PrintVisitor::visit(FunctionDefinition* e) {
	println("FunctionDefinition");
	level_++;
	std::stringstream ss;
	ss << e->getType()->getName() << " <- " << e->getName();
	println(ss.str());
	ParameterList* params = e->getParams();
	if (params) {
		params->accept(this);
	}
	e->getSl()->accept(this);
	level_--;
}

void PrintVisitor::visit(IfStatement* e) {
	// TODO implement
}

void PrintVisitor::visit(ParameterList* e) {
	// TODO implement
}

void PrintVisitor::visit(RandomForStatement* e) {
	// TODO implement
}

void PrintVisitor::visit(RandomIfStatement* e) {
	// TODO implement
}

void PrintVisitor::visit(ReturnStatement* e) {
	// TODO implement
}

void PrintVisitor::visit(Scope* e) {
	// TODO implement
}

void PrintVisitor::visit(StatementList* e) {
	println("StatementList");
	level_++;
	auto statements = e->getStatements();
	auto iter = statements.begin();
	auto end = statements.end();
	for (; iter != end; ++iter) {
		(*iter)->accept(this);
	}
	level_--;
}

void PrintVisitor::visit(ValueList* e) {
	// TODO implement
}

void PrintVisitor::visit(VariableDefinition* e) {
	// TODO implement
}

void PrintVisitor::indent() {
	for (int i = 0; i < level_; i++) {
		std::cout << " ";
	}
}

void PrintVisitor::print(const std::string& s) {
	indent();
	std::cout << s;
}

void PrintVisitor::println(const std::string& s) {
	print(s);
	std::cout << std::endl;
}