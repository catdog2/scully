#ifndef BINOP_H
#define BINOP_H

#include <string>
#include "AST/Expression.h"

class BinOp : public Expression {
public:
    BinOp(Expression* leftExp ,std::string op, Expression* rightExp);
    virtual ~BinOp();

    std::string getOp();
    Expression* getLeftExp();
    Expression* getRightExp();
    virtual void accept(ASTVisitor* visitor);



private:
    std::string op_;
    Expression* leftExp_;
    Expression* rightExp_;

};

#endif // BINOP_H
