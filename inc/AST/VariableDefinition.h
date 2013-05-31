#ifndef VARIABLEDEFINITION_H
#define VARIABLEDEFINITION_H

#include <string>

#include "AST/Statement.h"

class VariableDefinition : public Statement
{
public:
	VariableDefinition(int type, std::string name);
	virtual ~VariableDefinition();

	virtual void accept(ASTVisitor* visitor);

	// Type* getType();
	int getType();
	std::string getName();
private:
	// Type* type_
	int type_;
	std::string name_;
};

#endif // VARIABLEDEFINITION_H
