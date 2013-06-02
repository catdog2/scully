/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

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
