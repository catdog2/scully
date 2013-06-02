/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#ifndef LOADEXPRESSION_H
#define LOADEXPRESSION_H

#include <string>
#include "AST/Expression.h"

class LoadExpression : public Expression {
public:
	 LoadExpression(std::string id);
	virtual ~LoadExpression();

	virtual void accept(ASTVisitor *visitor);

	std::string getId();
private:
	std::string id_;
};

#endif // LOADEXPRESSION_H
