#ifndef FUNCTIONCALLEXPRESSION_H
#define FUNCTIONCALLEXPRESSION_H

#include <string>
#include "AST/ValueList.h"

class FunctionCallExpression : public Expression
{
public:
	FunctionCallExpression(std::string id, ValueList* values);
	virtual ~FunctionCallExpression();
	virtual void accept(ASTVisitor* visitor);

	std::string getId();
	ValueList* getValues();

private:
	std::string id_;
	ValueList* values_;

};

#endif // FUNCTIONCALLEXPRESSION_H
