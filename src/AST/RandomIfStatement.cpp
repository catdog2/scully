/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#include "AST/RandomIfStatement.h"
#include "AST/ASTVisitor.h"

RandomIfStatement::RandomIfStatement(Expression *prob, Statement *stmt) : prob_(prob),stmt_(stmt)
{
	//
}

RandomIfStatement::~RandomIfStatement() {
	//
}

void RandomIfStatement::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

Expression* RandomIfStatement::getProb() {
	return prob_;
}

Statement* RandomIfStatement::getStmt() {
	return stmt_;
}
