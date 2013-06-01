#ifndef BINOP_H
#define BINOP_H

#include <string>

enum class BinOp {
	EQUALS,
	LESS,
	PLUS,
	MINUS,
	TIMES,
	DIV
};

std::string binOpToString(BinOp op);

#endif // BINOP_H
