#ifndef FORSTATEMENT_H
#define FORSTATEMENT_H

#include "AST/Expression.h"
#include "AST/Statement.h"

class ForStatement : public Statement {
public:
	ForStatement(Statement* init, Expression* cond, Statement* step, Statement* stmt);
	virtual ~ForStatement();

	virtual void accept(ASTVisitor* visitor);

	Statement *getInit();
	Expression* getCond();
	Statement* getStep();
	Statement* getStmt();
private:
	Statement* init_;
	Expression* cond_;
	Statement* step_;
	Statement* stmt_;
};

#endif // FORSTATEMENT_H
