/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */


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
