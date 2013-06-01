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
