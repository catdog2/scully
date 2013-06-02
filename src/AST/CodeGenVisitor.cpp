#include "AST/CodeGenVisitor.h"
#include "llvm/Analysis/Verifier.h"
#include <iostream>

CodeGenVisitor::CodeGenVisitor(llvm::Module* module, llvm::FunctionPassManager *fpm, llvm::ExecutionEngine *ee) {
	builder_ = new llvm::IRBuilder<>(llvm::getGlobalContext());
	fpm_ = fpm;
	module_ = module;
	ee_ = ee;

	scope_ = 0;
	namedValues_.push_back(std::map<std::string, llvm::Value*>());

	// create external for putchar
	std::vector<llvm::Type*> argt(1, typeToLLVMType(Type::INT));
	llvm::FunctionType* ft = llvm::FunctionType::get(typeToLLVMType(Type::INT), argt, false);
	llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "put_char", module_);


	// create external for time_seed
	ft = llvm::FunctionType::get(typeToLLVMType(Type::INT), false);
	llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "time_seed", module_);

	// create external for random_if
	ft = llvm::FunctionType::get(typeToLLVMType(Type::BOOL), argt, false);
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
	if (!value_) {
		throw "error evaluating expression (lhs)";
	}
	llvm::Value* lhs = value_;

	e->getRightExp()->accept(this);
	if (!value_) {
		throw "error evaluating expression (rhs)";
	}
	llvm::Value* rhs = value_;

	if (lhs->getType() != rhs->getType()) {
		throw "lhs type of binop != rhs type of binop";
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
		value_ = builder_->CreateICmpEQ(lhs, rhs, "cmptmp");
		break;
	case BinOp::LESS:
		value_ = builder_->CreateICmpSLT(lhs, rhs, "cmptmp");
		break;
	default:
		throw "Unkown Operator, This is a Bug!";
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
	value_ = 0;
	e->getExpr()->accept(this);
	if (!value_) {
		throw "error evaluating expression";
	}
}

void CodeGenVisitor::visit(ForStatement* e)
{
	value_ = 0;
	e->getInit()->accept(this);

	value_ = 0;
	e->getCond()->accept(this);
	if (!value_) {
		throw "error evaluating expression";
	}

	llvm::Function* f = builder_->GetInsertBlock()->getParent();
	llvm::BasicBlock* loopBB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "loop", f);

	builder_->CreateBr(loopBB);
	builder_->SetInsertPoint(loopBB);

	value_ = 0;
	e->getStmt()->accept(this);

	value_ = 0;
	e->getStep()->accept(this);

	value_ = 0;
	e->getCond()->accept(this);
	if (!value_) {
		throw "error evaluating expression";
	}

	llvm::BasicBlock* afterBB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "afterLoop",f);

	builder_->CreateCondBr(value_, loopBB, afterBB);

	builder_->SetInsertPoint(afterBB);
}

void CodeGenVisitor::visit(FunctionCallExpression* e) {
	llvm::Function* cf = module_->getFunction(e->getId());
	if (!cf) {
		throw "function to call not found";
		return;
	}

	auto values = e->getValues()->getValues();
	if (cf->arg_size() != values.size()) {
		throw "argument size mismatch";
		return;
	}

	std::vector<llvm::Value*> args;
	auto iter = values.begin();
	auto end = values.end();
	for (; iter != end; ++iter) {
		Expression *expr = (*iter);
		expr->accept(this);
		if (!value_) {
			throw "error evaluating expression";
		}
		args.push_back(value_);
	}

	if (cf->getFunctionType()->getReturnType() == typeToLLVMType(Type::VOID)) {
		builder_->CreateCall(cf, args);
		// just handle void functions as if they returned 0
		value_ = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(0, 32, 10));
	} else {
		value_ = builder_->CreateCall(cf, args, "calltmp");
	}
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

	// validate generated code
	llvm::verifyFunction(*f);

	// optimize function
	fpm_->run(*f);

	value_ = f;
}

void CodeGenVisitor::visit(IfStatement* e) {
	value_ = 0;
	e->getCond()->accept(this);
	if (!value_) {
		throw "error evaluating expression";
	}

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
	// we can add an else part here later ...

	builder_->CreateBr(mergeBB);

	f->getBasicBlockList().push_back(mergeBB);
	builder_->SetInsertPoint(mergeBB);
}

void CodeGenVisitor::visit(ParameterList* e) {
	// NOT USED
}

void CodeGenVisitor::visit(RandomForStatement* e) {
	value_ = 0;
	e->getInit()->accept(this);

	value_ = 0;
	e->getProb()->accept(this);
	if (!value_) {
		throw "error evaluating expression";
	}

	llvm::Function* cf = module_->getFunction("random_if");
	llvm::Value* prob = builder_->CreateCall(cf, value_, "callTmp");

	llvm::Function* f = builder_->GetInsertBlock()->getParent();
	llvm::BasicBlock* loopBB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "loop", f);

	builder_->CreateBr(loopBB);
	builder_->SetInsertPoint(loopBB);

	value_ = 0;
	e->getStmt()->accept(this);

	value_ = 0;
	e->getStep()->accept(this);

	value_ = 0;
	e->getProb()->accept(this);
	if (value_ == 0) {
		throw "error evaluating expression";
	}

	llvm::BasicBlock* afterBB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "afterLoop",f);

	prob = builder_->CreateCall(cf,value_,"callTmp");
	builder_->CreateCondBr(prob, loopBB, afterBB);

	builder_->SetInsertPoint(afterBB);
}

void CodeGenVisitor::visit(RandomIfStatement* e) {
	value_ = 0;
	e->getProb()->accept(this);
	if (!value_) {
		throw "error evaluating expression";
	}

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
	if (e->getExpr() != 0) {
		e->getExpr()->accept(this);
		if (!value_) {
			throw "error evaluating expression";
		}

		builder_->CreateRet(value_);
	} else {
		builder_->CreateRetVoid();
	}
}

void CodeGenVisitor::visit(Scope* e) {
	scope_++;
	namedValues_.push_back(std::map<std::string, llvm::Value*>());
	e->getSl()->accept(this);
	namedValues_.pop_back();
	scope_--;
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
	// NOT USED
}

void CodeGenVisitor::visit(VariableDefinition* e) {
	llvm::Function* f = builder_->GetInsertBlock()->getParent();
	llvm::IRBuilder<> tmpBuilder(&(f->getEntryBlock()), f->getEntryBlock().begin());
	llvm::Value* alloca = tmpBuilder.CreateAlloca(typeToLLVMType(e->getType()), 0 , e->getName());
	putNamedValue(e->getName(), alloca);
}

void CodeGenVisitor::visit(LoadExpression *e) {
	llvm::Value* v = getNamedValue(e->getId());

	if (!v) {
		throw "unknown variable name";
	}

	value_ = builder_->CreateLoad(v, e->getId());
}

void CodeGenVisitor::JIT(Expression* e) {
	StatementList* sl = new StatementList();
	sl->addStatement(new ReturnStatement(e));
	FunctionDefinition* fd = new FunctionDefinition(Type::INT, "", new ParameterList(), sl);

	value_ = 0;
	fd->accept(this);

	if (!value_) {
		delete fd;
		throw "error evaluating expression";
	}

	llvm::Function* f = dynamic_cast<llvm::Function*>(value_);

	void* fPtr = ee_->getPointerToFunction(f);

	// some casting ... because we like magic
	int (*fP)() = (int (*)())(intptr_t)fPtr;

	std::cout << "Evaluated to: " << fP() << std::endl;

	// throw it away
	f->eraseFromParent();
}

void CodeGenVisitor::putNamedValue(const std::string& name, llvm::Value* value) {
	namedValues_[scope_][name] = value;
}

llvm::Value* CodeGenVisitor::getNamedValue(const std::string& name) {
	llvm::Value* v = 0;

	for (int i = scope_; i >= 0; i--) {
		if (namedValues_[i][name] != 0) {
			v = namedValues_[i][name];
			break;
		}
	}

	return v;
}
