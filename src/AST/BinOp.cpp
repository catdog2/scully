#include "AST/BinOp.h"
#include "AST/ASTVisitor.h"

BinOp::BinOp(Expression *leftExp, std::string op, Expression *rightExp) :
    leftExp_(leftExp), op_(op), rightExp_(rightExp) {
}

BinOp::~BinOp() {
    //
}

std::string BinOp::getOp() {
    return op_;
}

Expression* BinOp::getLeftExp() {
    return leftExp_;
}

Expression* BinOp::getRightExp() {
    return rightExp_;
}

void BinOp::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}
