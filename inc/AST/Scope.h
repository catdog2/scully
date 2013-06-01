#ifndef SCOPE_H
#define SCOPE_H

#include "AST/Statement.h"
#include "AST/StatementList.h"

class Scope : public Statement {
public:
	Scope(StatementList* sl);
	virtual ~Scope();

	virtual void accept(ASTVisitor* visitor);

	StatementList* getSl();
private:
	StatementList* sl_;
};

#endif // SCOPE_H
