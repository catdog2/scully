#ifndef RANDOMFORSTATEMENT_H
#define RANDOMFORSTATEMENT_H

#include "AST/Expression.h"
#include "AST/Statement.h"

class RandomForStatement : public Statement
{
public:
	RandomForStatement(Expression* init, Expression* prob, Expression* step, Statement* stmt);
	virtual ~RandomForStatement();

	virtual void accept(ASTVisitor *visitor);

	Expression* getInit();
	Expression* getProb();
	Expression* getStep();
	Statement* getStmt();
private:
	Expression* init_;
	Expression* prob_;
	Expression* step_;
	Statement* stmt_;
};

#endif // RANDOMFORSTATEMENT_H
