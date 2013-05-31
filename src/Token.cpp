/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#include "Token.h"

Token::Token(std::string text) : text_(text) {
	//
}

std::string Token::getText() {
	return text_;
}
