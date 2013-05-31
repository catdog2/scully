#ifndef ASTVISITOR_H
#define ASTVISITOR_H

#include "AssignmentExpression.h"
#include "ConstantExpression.h"
#include "VariableDefinition.h"
#include "ParameterList.h"

class ASTVisitor {
public:
	ASTVisitor();
	virtual ~ASTVisitor();

    virtual void visit(AssignmentExpression* e) = 0;
    virtual void visit(ConstantExpression* e) = 0;
	virtual void visit(ParameterList* e) = 0;
	virtual void visit(VariableDefinition* e) = 0;
};

#endif // ASTVISITOR_H
