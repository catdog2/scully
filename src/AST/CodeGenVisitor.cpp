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
	e->getLeftExp()->accept(this);
	llvm::Value* lhs = value_;
	e->getRightExp()->accept(this);
	llvm::Value* rhs = value_;

	if ((!lhs) || (!rhs)) {
		// TODO error
		return;
	}

//	switch (e->getOp()) {
//	case "+":
		value_ = builder_->CreateAdd(lhs, rhs, "addtmp");
//		break;
//	case "-":
//		value_ = builder_->CreateSub(lhs, rhs, "subtmp");
//		break;
//	case "*":
//		value_ = builder_->CreateMul(lhs, rhs, "multmp");
//		break;
//	case "/":
//		value_ = builder_->CreateSDiv(lhs, rhs, "divtmp");
//		break;
//	case "==":
//		value_ = builder_->CreateICmpEQ(lhs, rhs, "eqtmp");
//		break;
//	default:
//		// TODO error
//		break;
//	}

	value_->dump();
}

void CodeGenVisitor::visit(ConstantExpression* e) {
	value_ = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32, e->getValue(), 10));
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

void CodeGenVisitor::visit(LoadExpression *e) {
}

void CodeGenVisitor::createAnonymousFunction() {
	if (value_) {
		value_->dump();
	}
	// TODO implement
}
