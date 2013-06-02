/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#ifndef CONSTANTEXPRESSION_H
#define CONSTANTEXPRESSION_H

#include "AST/Expression.h"
#include <string>

class ConstantExpression : public Expression {
public:
	ConstantExpression(std::string value);
	virtual ~ConstantExpression();

	virtual void accept(ASTVisitor* visitor);

	std::string getValue();
private:
	std::string value_;
};

#endif // CONSTANTEXPRESSION_H
