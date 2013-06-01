#ifndef VALUELIST_H
#define VALUELIST_H

#include "AST/ASTElement.h"
#include "AST/Expression.h"
#include <vector>

class ValueList : public ASTElement {
public:
	ValueList();
	~ValueList();

	virtual void accept(ASTVisitor* visitor);

	void addValue(Expression* expr);
	std::vector<Expression*> getValues();
private:
	std::vector<Expression*> values_;
};

#endif // VALUELIST_H
