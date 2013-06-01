#ifndef ASTVISITOR_H
#define ASTVISITOR_H

#include "AssignmentExpression.h"
#include "BinOp.h"
#include "ConstantExpression.h"
#include "VariableDefinition.h"
#include "ParameterList.h"
#include "StatementList.h"

class ASTVisitor {
public:
	ASTVisitor();
	virtual ~ASTVisitor();

	virtual void visit(AssignmentExpression* e) = 0;
	virtual void visit(BinOp* e) = 0;
	virtual void visit(ConstantExpression* e) = 0;
	virtual void visit(ParameterList* e) = 0;
	virtual void visit(VariableDefinition* e) = 0;
    virtual void visit(StatementList* e) = 0;
};

#endif // ASTVISITOR_H
