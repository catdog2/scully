#include "AST/FunctionDefinition.h"
#include "AST/ASTVisitor.h"

FunctionDefinition::FunctionDefinition(Type type, std::string name, ParameterList *params, StatementList *sl) : type_(type), name_(name), params_(params), sl_(sl) {
	//
}

FunctionDefinition::~FunctionDefinition() {
	//
}

void FunctionDefinition::accept(ASTVisitor* visitor) {
	visitor->visit(this);
}

Type FunctionDefinition::getType() {
	return type_;
}

std::string FunctionDefinition::getName() {
	return name_;
}

ParameterList* FunctionDefinition::getParams() {
	return params_;
}

StatementList* FunctionDefinition::getSl() {
	return sl_;
}
