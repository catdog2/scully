/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#include "AST/BinOp.h"

std::string binOpToString(BinOp op) {
	switch (op) {
	case BinOp::DIV:
		return "/";
	case BinOp::EQUALS:
		return "==";
	case BinOp::LESS:
		return "<";
	case BinOp::MINUS:
		return "-";
	case BinOp::PLUS:
		return "+";
	case BinOp::TIMES:
		return "*";
	default:
		return "Unknown Op";
	}
}
