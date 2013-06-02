/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#include "AST/ReturnStatement.h"
#include "AST/ASTVisitor.h"

ReturnStatement::ReturnStatement(Expression* expr): expr_(expr) {
	//
}

ReturnStatement::~ReturnStatement() {
	//
}

void ReturnStatement::accept(ASTVisitor* visitor) {
	visitor->visit(this);
}

Expression* ReturnStatement::getExpr() {
	return expr_;
}
