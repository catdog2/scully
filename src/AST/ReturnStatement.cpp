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
