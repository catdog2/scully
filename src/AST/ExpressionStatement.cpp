/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#include "AST/ExpressionStatement.h"
#include "AST/ASTVisitor.h"

ExpressionStatement::ExpressionStatement(Expression *expr) : expr_(expr)
{
	//
}

ExpressionStatement::~ExpressionStatement() {

}

void ExpressionStatement::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

Expression* ExpressionStatement::getExpr() {
	return expr_;
}
