/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#ifndef STATEMENT_H
#define STATEMENT_H

#include "AST/ASTElement.h"

class Statement : public ASTElement {
public:
	Statement();
	virtual ~Statement();

	virtual void accept(ASTVisitor* visitor) = 0;
};

#endif // STATEMENT_H
