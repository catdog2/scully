#include "AST/RandomForStatement.h"
#include "AST/ASTVisitor.h"

RandomForStatement::RandomForStatement(Expression *init, Expression *prob, Expression *step, Statement *stmt) : init_(init),prob_(prob),step_(step),stmt_(stmt)
{
	//
}

RandomForStatement::~RandomForStatement() {
	//
}

void RandomForStatement::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

Expression* RandomForStatement::getInit() {
	return init_;
}

Expression* RandomForStatement::getProb() {
	return prob_;
}

Expression* RandomForStatement::getStep() {
	return step_;
}

Statement* RandomForStatement::getStmt() {
	return stmt_;
}

