#include "AST/IfStatement.h"
#include "AST/ASTVisitor.h"

IfStatement::IfStatement(Expression *cond, Statement *stmt) : cond_(cond),stmt_(stmt)
{
    //
}

IfStatement::~IfStatement(){
    //
}

void IfStatement::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

Expression* IfStatement::getCond() {
    return cond_;
}

Statement* IfStatement::getStmt() {
    return stmt_;
}
