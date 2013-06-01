#ifndef TYPE_H
#define TYPE_H

#include <string>

enum class Type { BOOL, INT, STRING, VOID };

std::string typeToString(Type type);

#endif // TYPE_H
