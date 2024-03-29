/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#ifndef PRINTVISITOR_H
#define PRINTVISITOR_H

#include "ASTVisitor.h"
#include <string>

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
	virtual void visit(LoadExpression* e);
private:
	int level_;
	void indent();
	void print(const std::string& s);
	void println(const std::string& s);
};

#endif // PRINTVISITOR_H
