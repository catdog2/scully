#ifndef BINOP_H
#define BINOP_H

#include "AST/Expression.h"

enum BinOp {
	OP_EQUALS,
	OP_LESS,
	OP_PLUS,
	OP_MINUS,
	OP_TIMES,
	OP_DIV
};

class BinOpExpression : public Expression {
public:
	BinOpExpression(Expression* leftExp ,BinOp op, Expression* rightExp);
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

#endif // BINOP_H
