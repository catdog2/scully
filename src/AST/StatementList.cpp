/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#include "AST/StatementList.h"
#include "AST/ASTVisitor.h"

StatementList::StatementList() {
    //
}

StatementList::~StatementList() {
    //
}

void StatementList::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}

void StatementList::addStatement(Statement* statement) {
    statements_.push_back(statement);
}

std::vector<Statement*> StatementList::getStatements() {
    return statements_;
}
