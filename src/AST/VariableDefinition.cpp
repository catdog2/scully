/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#include "AST/VariableDefinition.h"
#include "AST/ASTVisitor.h"

VariableDefinition::VariableDefinition(Type type, std::string name) : type_(type), name_(name) {
	//
}

VariableDefinition::~VariableDefinition() {
	//
}

void VariableDefinition::accept(ASTVisitor* visitor) {
	visitor->visit(this);
}

Type VariableDefinition::getType() {
	return type_;
}

std::string VariableDefinition::getName() {
	return name_;
}
