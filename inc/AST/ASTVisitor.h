#ifndef ASTVISITOR_H
#define ASTVISITOR_H

#include "AssignmentExpression.h"
#include "BinOp.h"
#include "ConstantExpression.h"
#include "IfStatement.h"
#include "ParameterList.h"
#include "Scope.h"
#include "StatementList.h"
#include "ValueList.h"
#include "VariableDefinition.h"
#include "ExpressionStatement.h"
#include "ReturnStatement.h"


class ASTVisitor {
public:
	ASTVisitor();
	virtual ~ASTVisitor();

	virtual void visit(AssignmentExpression* e) = 0;
	virtual void visit(BinOp* e) = 0;
	virtual void visit(ConstantExpression* e) = 0;
	virtual void visit(ExpressionStatement* e) = 0;
	virtual void visit(IfStatement* e) = 0;
	virtual void visit(ParameterList* e) = 0;
    virtual void visit(Scope* e) = 0;
    virtual void visit(StatementList* e) = 0;
	virtual void visit(ValueList* e) = 0;
	virtual void visit(VariableDefinition* e) = 0;
	virtual void visit(ReturnStatement* e) = 0;
};

#endif // ASTVISITOR_H
