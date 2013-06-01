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

	switch (e->getOp()) {
	case BinOp::PLUS:
	value_ = builder_->CreateAdd(lhs, rhs, "addtmp");
		break;
	case BinOp::MINUS:
		value_ = builder_->CreateSub(lhs, rhs, "subtmp");
		break;
	case BinOp::TIMES:
		value_ = builder_->CreateMul(lhs, rhs, "multmp");
		break;
	case BinOp::DIV:
		value_ = builder_->CreateSDiv(lhs, rhs, "divtmp");
		break;
	case BinOp::EQUALS:
		value_ = builder_->CreateICmpEQ(lhs, rhs, "eqtmp");
		break;
	default:
		// TODO error
		break;
	}

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
	llvm::Function* cf = module_->getFunction(e->getId());
	if (!cf) {
		// TODO error
		return;
	}

	auto values = e->getValues()->getValues();
	if (cf->arg_size() != values.size()) {
		// TODO error
		return;
	}

	std::vector<llvm::Value*> args;
	auto iter = values.begin();
	auto end = values.end();
	for (; iter != end; ++iter) {
		Expression *expr = (*iter);
		expr->accept(this);
		if (!value_) {
			// TODO error
		}
		args.push_back(value_);
	}

	value_ = builder_->CreateCall(cf, args, "calltmp");
	value_->dump();
}

void CodeGenVisitor::visit(FunctionDefinition* e) {
	std::vector<llvm::Type*> argTypes;
	auto params = e->getParams()->getParameters();
	auto iter = params.begin();
	auto end = params.end();
	for (; iter != end; ++iter) {
		Parameter& p = (*iter);
		argTypes.push_back(typeToLLVMType(p.first));
	}

	llvm::FunctionType* ft = llvm::FunctionType::get(typeToLLVMType(e->getType()), argTypes, false);
	llvm::Function *f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, e->getName(), module_);

	// If f conflicted, there was already something named 'Name'.  If it has a body,
	// don't allow redefinition or reextern.
	if (f->getName() != e->getName()) {
		f->eraseFromParent();
		f = module_->getFunction(e->getName());

		// If f already has a body, reject this.
		if (!f->empty()) {
			throw "redefinition of function";
		}

		// If f took a different number of args, reject.
		if (f->arg_size() != e->getParams()->getParameters().size()) {
			throw "redefinition of function with different # of arguments";
		}
	}

	// TODO set arg names

	value_ = f;
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
