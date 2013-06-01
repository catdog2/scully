#ifndef RANDOMFORSTATEMENT_H
#define RANDOMFORSTATEMENT_H

#include "AST/Expression.h"
#include "AST/Statement.h"

class RandomForStatement : public Statement
{
public:
	RandomForStatement(Statement *init, Expression* prob, Statement *step, Statement* stmt);
	virtual ~RandomForStatement();

	virtual void accept(ASTVisitor *visitor);

	Statement* getInit();
	Expression* getProb();
	Statement *getStep();
	Statement* getStmt();
private:
	Statement* init_;
	Expression* prob_;
	Statement* step_;
	Statement* stmt_;
};

#endif // RANDOMFORSTATEMENT_H
