/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#include "AST/ForStatement.h"
#include "AST/ASTVisitor.h"

ForStatement::ForStatement(Statement *init, Expression *cond, Statement *step, Statement *stmt) : init_(init), cond_(cond), step_(step), stmt_(stmt) {
	//
}

ForStatement::~ForStatement() {
	//
}

void ForStatement::accept(ASTVisitor* visitor) {
	visitor->visit(this);
}

Statement* ForStatement::getInit() {
	return init_;
}

Expression* ForStatement::getCond() {
	return cond_;
}

Statement* ForStatement::getStep() {
	return step_;
}

Statement* ForStatement::getStmt() {
	return stmt_;
}
