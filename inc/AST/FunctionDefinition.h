#ifndef FUNCTIONDEFINITION_H
#define FUNCTIONDEFINITION_H

#include "AST/ASTElement.h"
#include "AST/ParameterList.h"
#include "AST/StatementList.h"
#include "AST/Type.h"
#include <string>

class FunctionDefinition : public ASTElement {
public:
	FunctionDefinition(Type *type, std::string name, ParameterList* params, StatementList* sl);
	virtual ~FunctionDefinition();

	virtual void accept(ASTVisitor* visitor);

	Type* getType();
	std::string getName();
	ParameterList* getParams();
	StatementList* getSl();
private:
	Type* type_;
	std::string name_;
	ParameterList* params_;
	StatementList* sl_;
};

#endif // FUNCTIONDEFINITION_H
