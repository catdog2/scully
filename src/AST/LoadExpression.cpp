/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#include "AST/LoadExpression.h"
#include "AST/ASTVisitor.h"


LoadExpression::LoadExpression(std::string id): id_(id) {
	//
}

LoadExpression::~LoadExpression() {
	//
}

void LoadExpression::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

std::string LoadExpression::getId() {
	return id_;
}
