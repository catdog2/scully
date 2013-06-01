#ifndef PRINTVISITOR_H
#define PRINTVISITOR_H

#include "ASTVisitor.h"

class PrintVisitor : public ASTVisitor {
public:
	PrintVisitor();
	virtual ~PrintVisitor();

 	virtual void visit(AssignmentExpression* e);
	virtual void visit(BinOpExpression* e);
	virtual void visit(ConstantExpression* e);
	virtual void visit(ExpressionStatement* e);
	virtual void visit(ForStatement* e);
	virtual void visit(FunctionCallExpression* e);
	virtual void visit(FunctionDefinition* e);
	virtual void visit(IfStatement* e);
	virtual void visit(ParameterList* e);
	virtual void visit(RandomForStatement* e);
	virtual void visit(RandomIfStatement* e);
	virtual void visit(ReturnStatement* e);
	virtual void visit(Scope* e);
	virtual void visit(StatementList* e);
	virtual void visit(ValueList* e);
	virtual void visit(VariableDefinition* e);
};

#endif // PRINTVISITOR_H
