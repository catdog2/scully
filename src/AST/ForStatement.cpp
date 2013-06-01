#include "AST/ForStatement.h"
#include "AST/ASTVisitor.h"

ForStatement::ForStatement(Expression *init, Expression *cond, Expression *step, Statement *stmt) : init_(init), cond_(cond), step_(step), stmt_(stmt) {
	//
}

ForStatement::~ForStatement() {
	//
}

void ForStatement::accept(ASTVisitor* visitor) {
	visitor->visit(this);
}

Expression* ForStatement::getInit() {
	return init_;
}

Expression* ForStatement::getCond() {
	return cond_;
}

Expression* ForStatement::getStep() {
	return step_;
}

Statement* ForStatement::GetStmt() {
	return stmt_;
}
