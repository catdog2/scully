#ifndef TYPE_H
#define TYPE_H

#include "llvm/Type.h"
#include <string>

enum class Type { BOOL, INT, STRING, VOID };

std::string typeToString(Type type);
llvm::Type* typeToLLVMType(Type type);

#endif // TYPE_H
