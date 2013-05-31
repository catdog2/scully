#include "AST/Type.h"

Type::Type(std::string name) : name_(name) {
	//
}

std::string Type::getName() {
	return name_;
}
