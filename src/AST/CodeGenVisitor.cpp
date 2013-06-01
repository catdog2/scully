#include "AST/CodeGenVisitor.h"

CodeGenVisitor::CodeGenVisitor(llvm::Module* module, llvm::FunctionPassManager *fpm) {
	builder_ = new llvm::IRBuilder<>(llvm::getGlobalContext());
	module_ = module;
	fpm_ = fpm;
}

CodeGenVisitor::~CodeGenVisitor() {
	delete builder_;
}

void CodeGenVisitor::visit(AssignmentExpression* e) {
}

void CodeGenVisitor::visit(BinOpExpression* e) {
}

void CodeGenVisitor::visit(ConstantExpression* e) {
}

void CodeGenVisitor::visit(ExpressionStatement* e) {
}

void CodeGenVisitor::visit(ForStatement* e) {
}

void CodeGenVisitor::visit(FunctionCallExpression* e) {
}

void CodeGenVisitor::visit(FunctionDefinition* e) {
}

void CodeGenVisitor::visit(IfStatement* e) {
}

void CodeGenVisitor::visit(ParameterList* e) {
}

void CodeGenVisitor::visit(RandomForStatement* e) {
}

void CodeGenVisitor::visit(RandomIfStatement* e) {
}

void CodeGenVisitor::visit(ReturnStatement* e) {
}

void CodeGenVisitor::visit(Scope* e) {
}

void CodeGenVisitor::visit(StatementList* e) {
}

void CodeGenVisitor::visit(ValueList* e) {
}

void CodeGenVisitor::visit(VariableDefinition* e) {
}
