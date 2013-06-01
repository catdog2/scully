#ifndef RETURNSTATEMENT_H
#define RETURNSTATEMENT_H

#include "AST/Statement.h"
#include "AST/Expression.h"

class ReturnStatement : public Statement {
public:
	ReturnStatement(Expression* expr);
	virtual ~ReturnStatement();
	virtual void accept(ASTVisitor *visitor);
	Expression* getExpr();
private:
	Expression* expr_;
};

#endif // RETURNSTATEMENT_H
