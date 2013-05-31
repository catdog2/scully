#include "AST/ConstantExpression.h"
#include "AST/ASTVisitor.h"

ConstantExpression::ConstantExpression(std::string value) : value_(value) {
	//
}

ConstantExpression::~ConstantExpression() {
}

void ConstantExpression::accept(ASTVisitor* visitor) {
	visitor->visit(this);
}

std::string ConstantExpression::getValue() {
	return value_;
}
