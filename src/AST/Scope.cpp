#include "AST/Scope.h"
#include "AST/ASTVisitor.h"

Scope::Scope(Statement* stmt) : stmt_(stmt) {
	//
}

Scope::~Scope() {
	//
}

void Scope::accept(ASTVisitor* visitor) {
	visitor->visit(this);
}

Statement* Scope::getStmt() {
	return stmt_;
}
