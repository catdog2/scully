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
	println("BinOpExpression");
	level_++;
	std::stringstream ss;
	std::string opStr;
	switch (e->getOp()) {
	case OP_DIV:
		opStr = "/";
		break;
	case OP_EQUALS:
		opStr = "==";
		break;
	case OP_LESS:
		opStr = "<";
		break;
	case OP_MINUS:
		opStr = "-";
		break;
	case OP_PLUS:
		opStr = "+";
		break;
	case OP_TIMES:
		opStr = "*";
		break;
	default:
		opStr = "Unknown Op";
		break;
	}


	ss << "Operator: " << opStr;
	println(ss.str());
	println("LHS:");
	e->getLeftExp()->accept(this);
	println("RHS:");
	e->getRightExp()->accept(this);
	level_--;
}

void PrintVisitor::visit(ConstantExpression* e) {
	println("ConstantExpression");
	level_++;
	println(e->getValue());
	level_--;
}

void PrintVisitor::visit(ExpressionStatement* e) {
	println("ExpressionStatement");
	level_++;
	e->getExpr()->accept(this);
	level_--;
}

void PrintVisitor::visit(ForStatement* e) {
	println("ForStatement");
	level_++;
	println("Init:");
	e->getInit()->accept(this);
	println("Cond:");
	e->getCond()->accept(this);
	println("Step:");
	e->getStep()->accept(this);
	println("Stmt:");
	e->getStmt()->accept(this);
	level_--;
}

void PrintVisitor::visit(FunctionCallExpression* e) {
	println("FunctionCallExpression");
	level_++;
	std::stringstream ss;
	ss << "Name: " << e->getId();
	println(ss.str());
	println("Values:");
	e->getValues()->accept(this);
	level_--;
}

void PrintVisitor::visit(FunctionDefinition* e) {
	println("FunctionDefinition");
	level_++;
	std::stringstream ss;
	ss << "Name: " << e->getName();
	println(ss.str());
	ss.str("");
	ss.clear();
	ss << "Type: " << e->getType();
	println(ss.str());
	ParameterList* params = e->getParams();
	if (params) {
		params->accept(this);
	}
	e->getSl()->accept(this);
	level_--;
}

void PrintVisitor::visit(IfStatement* e) {
	println("IfStatement");
	level_++;
	println("Cond:");
	e->getCond()->accept(this);
	println("Stmt:");
	e->getStmt()->accept(this);
	level_--;
}

void PrintVisitor::visit(ParameterList* e) {
	println("ParameterList");
	level_++;
	auto params = e->getParameters();
	auto iter = params.begin();
	auto end = params.end();
	for (; iter != end; ++iter) {
		Parameter& p = (*iter);
		std::stringstream ss;
		ss << "Name: " << p.second;
		println(ss.str());
		ss.str("");
		ss.clear();
		ss << "Type: " << p.first->getName();
		println(ss.str());
	}
	level_--;
}

void PrintVisitor::visit(RandomForStatement* e) {
	println("RandomForStatement");
	level_++;
	println("Init:");
	e->getInit()->accept(this);
	println("Probability:");
	e->getProb()->accept(this);
	println("Step:");
	e->getStep()->accept(this);
	println("Stmt:");
	e->getStmt()->accept(this);
	level_--;
}

void PrintVisitor::visit(RandomIfStatement* e) {
	println("RandomIfStatement");
	level_++;
	println("Probability:");
	e->getProb()->accept(this);
	println("Stmt:");
	e->getStmt()->accept(this);
	level_--;
}

void PrintVisitor::visit(ReturnStatement* e) {
	println("ReturnStatement");
	level_++;
	e->getExpr()->accept(this);
	level_--;
}

void PrintVisitor::visit(Scope* e) {
	println("Scope");
	level_++;
	e->getSl()->accept(this);
	level_--;
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
	println("ValueList");
	level_++;
	auto values = e->getValues();
	auto iter = values.begin();
	auto end = values.end();
	for(; iter != end; ++iter) {
		(*iter)->accept(this);
	}
	level_--;
}

void PrintVisitor::visit(VariableDefinition* e) {
	println("VariableDefinition");
	level_++;
	std::stringstream ss;
	ss << "Name: " << e->getName();
	println(ss.str());
	ss.str("");
	ss.clear();
	ss << "Type: " << e->getType()->getName();
	println(ss.str());
	level_--;
}

void PrintVisitor::visit(LoadExpression *e) {
	println("LoadExpression");
	level_++;
	std::stringstream ss;
	ss << "Name: " << e->getId();
	println(ss.str());
	level_--;
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
