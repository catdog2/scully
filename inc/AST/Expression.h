#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "AST/ASTElement.h"

class Expression : public ASTElement {
public:
	Expression();
	virtual ~Expression();

	virtual void accept(ASTVisitor* visitor) = 0;
};

#endif // EXPRESSION_H
