/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#include "AST/BinOpExpression.h"
#include "AST/ASTVisitor.h"

BinOpExpression::BinOpExpression(Expression *leftExp, BinOp op, Expression *rightExp) :
    leftExp_(leftExp), op_(op), rightExp_(rightExp) {
}

BinOpExpression::~BinOpExpression() {
    //
}

BinOp BinOpExpression::getOp() {
    return op_;
}

Expression* BinOpExpression::getLeftExp() {
    return leftExp_;
}

Expression* BinOpExpression::getRightExp() {
    return rightExp_;
}

void BinOpExpression::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}
