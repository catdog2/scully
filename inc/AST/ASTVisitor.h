#ifndef ASTVISITOR_H
#define ASTVISITOR_H

#include "VariableDefinition.h"
#include "ParameterList.h"

class ASTVisitor {
public:
	ASTVisitor();
	virtual ~ASTVisitor();

	virtual void visit(ParameterList* e) = 0;
	virtual void visit(VariableDefinition* e) = 0;
};

#endif // ASTVISITOR_H
