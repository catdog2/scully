#include "AST/Type.h"

std::string typeToString(Type type) {
	switch (type) {
	case Type::BOOL:
		return "bool";
	case Type::INT:
		return "int";
	case Type::STRING:
		return "string";
	case Type::VOID:
		return "void";
	default:
		return "ERROR";
  }
}
