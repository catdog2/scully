#include "AST/AssignmentExpression.h"
#include "AST/ASTVisitor.h"

AssignmentExpression::AssignmentExpression(std::string id, Expression *expr) : id_(id), expr_(expr) {
	//
}

AssignmentExpression::~AssignmentExpression() {
	//
}

void AssignmentExpression::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

std::string AssignmentExpression::getId() {
	return id_;
}

Expression* AssignmentExpression::getExpr() {
	return expr_;
}
