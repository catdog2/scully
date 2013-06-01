#include "AST/Scope.h"
#include "AST/ASTVisitor.h"

Scope::Scope(StatementList *sl) : sl_(sl) {
	//
}

Scope::~Scope() {
	//
}

void Scope::accept(ASTVisitor* visitor) {
	visitor->visit(this);
}

StatementList* Scope::getSl() {
	return sl_;
}
