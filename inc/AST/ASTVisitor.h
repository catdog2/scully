#ifndef ASTVISITOR_H
#define ASTVISITOR_H

#include "AssignmentExpression.h"
#include "BinOp.h"
#include "ConstantExpression.h"
#include "ExpressionStatement.h"
#include "ForStatement.h"
#include "FunctionCallExpression.h"
#include "FunctionDefinition.h"
#include "IfStatement.h"
#include "ParameterList.h"
#include "RandomForStatement.h"
#include "RandomIfStatement.h"
#include "ReturnStatement.h"
#include "Scope.h"
#include "StatementList.h"
#include "ValueList.h"
#include "VariableDefinition.h"


class ASTVisitor {
public:
	ASTVisitor();
	virtual ~ASTVisitor();

	virtual void visit(AssignmentExpression* e) = 0;
	virtual void visit(BinOp* e) = 0;
	virtual void visit(ConstantExpression* e) = 0;
	virtual void visit(ExpressionStatement* e) = 0;
	virtual void visit(ForStatement* e) = 0;
	virtual void visit(FunctionCallExpression* e) = 0;
	virtual void visit(FunctionDefinition* e) = 0;
	virtual void visit(IfStatement* e) = 0;
	virtual void visit(ParameterList* e) = 0;
	virtual void visit(RandomForStatement* e) = 0;
	virtual void visit(RandomIfStatement* e) = 0;
	virtual void visit(ReturnStatement* e) = 0;
	virtual void visit(Scope* e) = 0;
	virtual void visit(StatementList* e) = 0;
	virtual void visit(ValueList* e) = 0;
	virtual void visit(VariableDefinition* e) = 0;

};

#endif // ASTVISITOR_H
