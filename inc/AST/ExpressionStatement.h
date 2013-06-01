#ifndef EXPRESSIONSTATEMENT_H
#define EXPRESSIONSTATEMENT_H

#include "AST/Expression.h"
#include "AST/Statement.h"

class ExpressionStatement : public Statement
{
public:
	ExpressionStatement(Expression* expr);
	virtual ~ExpressionStatement();

	virtual void accept(ASTVisitor* visitor);

	Expression* getExpr();
private:
	Expression* expr_;
};

#endif // EXPRESSIONSTATEMENT_H
