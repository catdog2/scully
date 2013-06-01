#ifndef FORSTATEMENT_H
#define FORSTATEMENT_H

#include "AST/Expression.h"
#include "AST/Statement.h"

class ForStatement : public Statement {
public:
	ForStatement(Expression* init, Expression* cond, Expression* step, Statement* stmt);
	virtual ~ForStatement();

	virtual void accept(ASTVisitor* visitor);

	Expression* getInit();
	Expression* getCond();
	Expression* getStep();
	Statement* getStmt();
private:
	Expression* init_;
	Expression* cond_;
	Expression* step_;
	Statement* stmt_;
};

#endif // FORSTATEMENT_H
