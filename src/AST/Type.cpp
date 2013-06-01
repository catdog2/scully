#include "AST/Type.h"
#include "llvm/DerivedTypes.h"
#include "llvm/LLVMContext.h"

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

llvm::Type* typeToLLVMType(Type type) {
	switch (type) {
	case Type::BOOL:
		return llvm::Type::getInt1Ty(llvm::getGlobalContext());
	case Type::INT:
		return llvm::Type::getInt32Ty(llvm::getGlobalContext());
	case Type::STRING:
		return llvm::Type::getInt8PtrTy(llvm::getGlobalContext());
	case Type::VOID:
		return llvm::Type::getVoidTy(llvm::getGlobalContext());
	default:
		// TODO error
		return llvm::Type::getVoidTy(llvm::getGlobalContext());
	}
}
