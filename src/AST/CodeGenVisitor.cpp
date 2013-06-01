#include "AST/CodeGenVisitor.h"
#include <iostream>

CodeGenVisitor::CodeGenVisitor(llvm::Module* module, llvm::FunctionPassManager *fpm) {
	builder_ = new llvm::IRBuilder<>(llvm::getGlobalContext());
	module_ = module;
	fpm_ = fpm;

	// create external for random_if
	std::vector<llvm::Type*> argt(1, typeToLLVMType(Type::INT));
	llvm::FunctionType* ft = llvm::FunctionType::get(typeToLLVMType(Type::BOOL), argt, false);
	llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "random_if", module_);
}

CodeGenVisitor::~CodeGenVisitor() {
	delete builder_;
}

void CodeGenVisitor::visit(AssignmentExpression* e) {
	value_ = 0;
	e->getExpr()->accept(this);

	if (value_ == 0) {
		throw "error creating expression";
	}

	builder_->CreateStore(value_, getNamedValue(e->getId()));
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
	case BinOp::LESS:
		value_ = builder_->CreateICmpSLT(lhs, rhs, "eqtmp");
		break;
	default:
		// TODO error
		break;
	}
}

void CodeGenVisitor::visit(ConstantExpression* e) {
	if(e->getValue() == "true") {
		value_ = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(1, 1, 10));
	} else if(e->getValue() == "false") {
		value_ = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(1, 0, 10));
	} else {
		value_ = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32, e->getValue(), 10));
	}
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

	// set arg names
	unsigned idx = 0;
	for(auto ai = f->arg_begin(); idx != params.size(); ++ai, ++idx) {
		ai->setName(params[idx].second);
		//std::cout << "naming parameter " << idx << ": " << params[idx].second << std::endl;

		// add to symbol table
		putNamedValue(params[idx].second, ai);
	}

	llvm::BasicBlock* bb = llvm::BasicBlock::Create(llvm::getGlobalContext(), "entry", f);
	builder_->SetInsertPoint(bb);

	// put all arguments on the stack
	idx = 0;
	for(auto ai = f->arg_begin(); idx != params.size(); ++ai, ++idx) {
		llvm::Value* alloca = builder_->CreateAlloca(typeToLLVMType(params[idx].first) ,0 , params[idx].second);
		builder_->CreateStore(ai, alloca);
		putNamedValue(params[idx].second, alloca);
	}

	// build code for the statements
	e->getSl()->accept(this);

	// TODO we might want to call verifyFunction ...
	value_ = f;
}

void CodeGenVisitor::visit(IfStatement* e) {
	value_ = 0;
	e->getCond()->accept(this);

	llvm::Function* f = builder_->GetInsertBlock()->getParent();
	llvm::BasicBlock* thenBB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "then", f);
	llvm::BasicBlock* elseBB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "else");
	llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "merge");

	builder_->CreateCondBr(value_, thenBB, elseBB);

	builder_->SetInsertPoint(thenBB);
	e->getStmt()->accept(this);

	builder_->CreateBr(mergeBB);

	f->getBasicBlockList().push_back(elseBB);
	builder_->SetInsertPoint(elseBB);
	// we cna add an else part here later ...

	builder_->CreateBr(mergeBB);

	f->getBasicBlockList().push_back(mergeBB);
	builder_->SetInsertPoint(mergeBB);
}

void CodeGenVisitor::visit(ParameterList* e) {
}

void CodeGenVisitor::visit(RandomForStatement* e) {
}

void CodeGenVisitor::visit(RandomIfStatement* e) {
	value_ = 0;
	e->getProb()->accept(this);
	llvm::Function* cf = module_->getFunction("random_if");
	llvm::Value* cond = builder_->CreateCall(cf,value_,"callTmp");

	llvm::Function* f = builder_->GetInsertBlock()->getParent();
	llvm::BasicBlock* thenBB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "then", f);
	llvm::BasicBlock* elseBB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "else");
	llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "merge");

	builder_->CreateCondBr(cond, thenBB, elseBB);

	// then
	builder_->SetInsertPoint(thenBB);
	e->getStmt()->accept(this);

	builder_->CreateBr(mergeBB);

	f->getBasicBlockList().push_back(elseBB);
	builder_->SetInsertPoint(elseBB);

	builder_->CreateBr(mergeBB);

	f->getBasicBlockList().push_back(mergeBB);
	builder_->SetInsertPoint(mergeBB);
}

void CodeGenVisitor::visit(ReturnStatement* e) {
	e->getExpr()->accept(this);
	builder_->CreateRet(value_);
}

void CodeGenVisitor::visit(Scope* e) {
	// TODO increment scope
	e->getSl()->accept(this);
	// TODO decrement scope
}

void CodeGenVisitor::visit(StatementList* e) {
	auto statements = e->getStatements();
	auto iter = statements.begin();
	auto end = statements.end();
	for (; iter != end; ++iter) {
		(*iter)->accept(this);
	}
}

void CodeGenVisitor::visit(ValueList* e) {
}

void CodeGenVisitor::visit(VariableDefinition* e) {
	llvm::Function* f = builder_->GetInsertBlock()->getParent();
	llvm::IRBuilder<> tmpBuilder(&(f->getEntryBlock()), f->getEntryBlock().begin());
	llvm::Value* alloca = tmpBuilder.CreateAlloca(typeToLLVMType(e->getType()), 0 , e->getName());
	putNamedValue(e->getName(), alloca);
}

void CodeGenVisitor::visit(LoadExpression *e) {
	value_ = getNamedValue(e->getId());
}

void CodeGenVisitor::createAnonymousFunction() {
	if (value_) {
		value_->dump();
	}
	// TODO implement
}

void CodeGenVisitor::putNamedValue(const std::string& name, llvm::Value* value) {
	namedValues_[name] = value;
}

llvm::Value* CodeGenVisitor::getNamedValue(const std::string& name) {
	return namedValues_[name];
}
