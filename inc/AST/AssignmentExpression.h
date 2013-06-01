#ifndef ASSIGNMENTEXPRESSION_H
#define ASSIGNMENTEXPRESSION_H

#include "AST/Expression.h"
#include <string>

class AssignmentExpression : public Expression {
public:
	AssignmentExpression(std::string id, Expression* expr);
	virtual ~AssignmentExpression();

	virtual void accept(ASTVisitor *visitor);

	std::string getId();
	Expression* getExpr();
private:
	std::string id_;
	Expression* expr_;
};

#endif // ASSIGNMENTEXPRESSION_H
