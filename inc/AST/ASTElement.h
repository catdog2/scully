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
