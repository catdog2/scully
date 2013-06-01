#include "AST/ValueList.h"
#include "AST/ASTVisitor.h"

ValueList::ValueList() {
	//
}

ValueList::~ValueList() {
	//
}

void ValueList::accept(ASTVisitor* visitor) {
	visitor->visit(this);
}

void ValueList::addValue(Expression* expr) {
	values_.push_back(expr);
}

std::vector<Expression*> ValueList::getValues() {
	return values_;
}
