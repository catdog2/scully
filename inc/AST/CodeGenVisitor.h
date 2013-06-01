#ifndef CODEGENVISITOR_H
#define CODEGENVISITOR_H

#include "ASTVisitor.h"
#include "llvm/DerivedTypes.h"
#include "llvm/IRBuilder.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Analysis/Verifier.h"
#include <string>

class CodeGenVisitor : public ASTVisitor {
public:
	CodeGenVisitor();
	virtual ~CodeGenVisitor();

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
private:
};

#endif // CODEGENVISITOR_H
