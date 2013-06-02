/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#ifndef STATEMENTLIST_H
#define STATEMENTLIST_H

#include <vector>
#include "AST/ASTElement.h"
#include "AST/Statement.h"

class StatementList : public ASTElement
{
public:
    StatementList();
    virtual ~StatementList();
    virtual void accept(ASTVisitor* visitor);
    void addStatement(Statement* statement);
    std::vector<Statement*> getStatements();
private:
    std::vector<Statement*> statements_;
};

#endif // STATEMENTLIST_H
