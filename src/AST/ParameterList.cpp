#include "AST/ParameterList.h"
#include "AST/ASTVisitor.h"

ParameterList::ParameterList() {
	//
}

ParameterList::~ParameterList() {
	//
}

void ParameterList::accept(ASTVisitor* visitor) {
	visitor->visit(this);
}

void ParameterList::addParameter(Type type, std::string name) {
	params_.push_back(Parameter(type, name));
}

std::vector<Parameter> ParameterList::getParameters() {
	return params_;
}
