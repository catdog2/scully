#include "AST/RandomForStatement.h"
#include "AST/ASTVisitor.h"

RandomForStatement::RandomForStatement(Statement *init, Expression *prob, Statement *step, Statement *stmt) : init_(init),prob_(prob),step_(step),stmt_(stmt)
{
	//
}

RandomForStatement::~RandomForStatement() {
	//
}

void RandomForStatement::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

Statement *RandomForStatement::getInit() {
	return init_;
}

Expression* RandomForStatement::getProb() {
	return prob_;
}

Statement* RandomForStatement::getStep() {
	return step_;
}

Statement* RandomForStatement::getStmt() {
	return stmt_;
}

