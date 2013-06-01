#ifndef VARIABLEDEFINITION_H
#define VARIABLEDEFINITION_H

#include <string>

#include "AST/Statement.h"
#include "AST/Type.h"

class VariableDefinition : public Statement
{
public:
	VariableDefinition(Type type, std::string name);
	virtual ~VariableDefinition();

	virtual void accept(ASTVisitor* visitor);

	Type getType();
	std::string getName();
private:
	Type type_;
	std::string name_;
};

#endif // VARIABLEDEFINITION_H
