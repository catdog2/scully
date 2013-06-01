#ifndef IFSTATEMENT_H
#define IFSTATEMENT_H

#include "AST/Expression.h"
#include "AST/Statement.h"

class IfStatement : public Statement
{
public:
    IfStatement(Expression* cond, Statement* stmt);
    virtual ~IfStatement();

    virtual void accept(ASTVisitor *visitor);

    Expression* getCond();
    Statement* getStmt();
private:
    Expression* cond_;
    Statement* stmt_;

};

#endif // IFSTATEMENT_H
