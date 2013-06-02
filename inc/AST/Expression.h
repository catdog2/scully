/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "AST/ASTElement.h"

class Expression : public ASTElement {
public:
	Expression();
	virtual ~Expression();

	virtual void accept(ASTVisitor* visitor) = 0;
};

#endif // EXPRESSION_H
