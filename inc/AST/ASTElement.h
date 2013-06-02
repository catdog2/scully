/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#ifndef ASTELEMENT_H
#define ASTELEMENT_H

class ASTVisitor;

class ASTElement {
public:
	ASTElement();
	virtual ~ASTElement();

	virtual void accept(ASTVisitor* visitor) = 0;
};

#endif // ASTELEMENT_H
