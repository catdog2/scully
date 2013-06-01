#ifndef PARAMETERLIST_H
#define PARAMETERLIST_H

#include "AST/ASTElement.h"
#include "AST/Type.h"
#include <vector>

typedef std::pair<Type, std::string> Parameter;

class ParameterList : public ASTElement {
public:
	ParameterList();
	virtual ~ParameterList();

	virtual void accept(ASTVisitor* visitor);

	void addParameter(Type type, std::string name);
	std::vector<Parameter> getParameters();
private:
	std::vector<Parameter> params_;
};

#endif // PARAMETERLIST_H
