#include "AST/VariableDefinition.h"
#include "AST/ASTVisitor.h"

VariableDefinition::VariableDefinition(int type, std::string name) : type_(type), name_(name) {
	//
}

VariableDefinition::~VariableDefinition() {
	//
}

void VariableDefinition::accept(ASTVisitor* visitor) {
	visitor->visit(this);
}

int VariableDefinition::getType() {
	return type_;
}

std::string VariableDefinition::getName() {
	return name_;
}
