#ifndef SCOPE_H
#define SCOPE_H

#include "AST/Statement.h"

class Scope : public Statement {
public:
	Scope(Statement* stmt);
	virtual ~Scope();

	virtual void accept(ASTVisitor* visitor);

	Statement* getStmt();
private:
	Statement* stmt_;
};

#endif // SCOPE_H
