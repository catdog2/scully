/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token {
public:
	Token(std::string text);
	std::string getText();
private:
	std::string text_;
};

#endif // TOKEN_H
