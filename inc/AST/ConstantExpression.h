#ifndef CONSTANTEXPRESSION_H
#define CONSTANTEXPRESSION_H

#include "AST/Expression.h"
#include <string>

class ConstantExpression : public Expression {
public:
	ConstantExpression(std::string value);
	virtual ~ConstantExpression();

	virtual void accept(ASTVisitor* visitor);

	std::string getValue();
private:
	std::string value_;
};

#endif // CONSTANTEXPRESSION_H
