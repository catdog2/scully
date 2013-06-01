#ifndef RANDOMIFSTATEMENT_H
#define RANDOMIFSTATEMENT_H

#include "AST/Expression.h"
#include "AST/Statement.h"

class RandomIfStatement : public Statement
{
public:
	RandomIfStatement(Expression* prob, Statement* stmt);
	virtual ~RandomIfStatement();

	virtual void accept(ASTVisitor *visitor);

	Expression* getProb();
	Statement* getStmt();
private:
	Expression* prob_;
	Statement* stmt_;
};

#endif // RANDOMIFSTATEMENT_H
