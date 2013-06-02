/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#include "AST/FunctionCallExpression.h"
#include "AST/ASTVisitor.h"

FunctionCallExpression::FunctionCallExpression(std::string id, ValueList* values):
	id_(id), values_(values) {
	//
}

FunctionCallExpression::~FunctionCallExpression() {
	//
}

void FunctionCallExpression::accept(ASTVisitor* visitor) {
	visitor->visit(this);
}

std::string FunctionCallExpression::getId() {
	return id_;
}

ValueList*FunctionCallExpression::getValues() {
	return values_;
}


