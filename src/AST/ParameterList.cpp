#include "AST/ParameterList.h"
#include "AST/ASTVisitor.h"
#include <iostream>

ParameterList::ParameterList() {
	//
}

ParameterList::~ParameterList() {
	//
}

void ParameterList::accept(ASTVisitor* visitor) {
	visitor->visit(this);
}

void ParameterList::addParameter(Type* type, std::string name) {
	std::cout << "added parameter of type " << type->getName() << " and name " << name << std::endl;
	params_.push_back(Parameter(type, name));
}

std::vector<Parameter> ParameterList::getParameters() {
	return params_;
}
