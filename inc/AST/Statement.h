#ifndef STATEMENT_H
#define STATEMENT_H

#include "AST/ASTElement.h"

class Statement : public ASTElement {
public:
	Statement();
	virtual ~Statement();

	virtual void accept(ASTVisitor* visitor) = 0;
};

#endif // STATEMENT_H
