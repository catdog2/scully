#ifndef ASTVISITOR_H
#define ASTVISITOR_H

#include "VariableDefinition.h"

class ASTVisitor {
public:
	ASTVisitor();
	virtual ~ASTVisitor();

	virtual void visit(VariableDefinition* e) = 0;
};

#endif // ASTVISITOR_H
