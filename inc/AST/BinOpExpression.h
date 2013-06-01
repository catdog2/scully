#ifndef BINOPEXPRESSION_H
#define BINOPEXPRESSION_H

#include "AST/Expression.h"
#include "AST/BinOp.h"

class BinOpExpression : public Expression {
public:
	BinOpExpression(Expression* leftExp, BinOp op, Expression* rightExp);
    virtual ~BinOpExpression();

	BinOp getOp();
    Expression* getLeftExp();
    Expression* getRightExp();
    virtual void accept(ASTVisitor* visitor);



private:
	BinOp op_;
    Expression* leftExp_;
    Expression* rightExp_;

};

#endif // BINOPEXPRESSION_H
