%include {

#include <cstdio>
#include <iostream>
#include <string>
#include <assert.h>

#include "Token.h"

#include "AST/ASTElement.h"
#include "AST/AssignmentExpression.h"
#include "AST/BinOpExpression.h"
#include "AST/CodeGenVisitor.h"
#include "AST/ConstantExpression.h"
#include "AST/Expression.h"
#include "AST/ExpressionStatement.h"
#include "AST/ForStatement.h"
#include "AST/FunctionCallExpression.h"
#include "AST/FunctionDefinition.h"
#include "AST/IfStatement.h"
#include "AST/LoadExpression.h"
#include "AST/ParameterList.h"
#include "AST/PrintVisitor.h"
#include "AST/RandomForStatement.h"
#include "AST/RandomIfStatement.h"
#include "AST/ReturnStatement.h"
#include "AST/Scope.h"
#include "AST/Statement.h"
#include "AST/StatementList.h"
#include "AST/Type.h"
#include "AST/ValueList.h"
#include "AST/VariableDefinition.h"

}

%name scullyParser

%token_type {Token*}
%extra_argument{CodeGenVisitor* cv}

// whitespace and comments
%type T_WHITESPACE {int}

%right T_ASSIGN.
%left T_EQUALS.
%left T_LESS.
%left T_PLUS T_MINUS.
%left T_TIMES T_DIV.

%syntax_error {
	std::cerr << "Syntax error!" << std::endl;
}

%parse_failure {
	std::cerr << "Parser Failed!" << std::endl;
}

%type program {int}
program ::= fundef(F).								{ PrintVisitor* pv = new PrintVisitor; F->accept(pv); F->accept(cv); delete pv; }
program ::= expr(E).								{ PrintVisitor* pv = new PrintVisitor; E->accept(pv); E->accept(cv); delete pv; }

%type fundef {FunctionDefinition*}
fundef(A) ::= type(T) T_IDENTIFIER(ID) T_LPAREN params(P) T_RPAREN T_BEGIN statements(S) T_END.
													{ A = new FunctionDefinition(T, ID->getText(), P, S); }

%type type {Type}
type(A) ::= T_BOOL.									{ A = Type::BOOL; }
type(A) ::= T_INT.									{ A = Type::INT; }
type(A) ::= T_STRING.								{ A = Type::STRING; }
type(A) ::= T_VOID.									{ A = Type::VOID; }

%type params {ParameterList*}
params(A) ::= .										{ A = new ParameterList(); }
params(A) ::= type(T) T_IDENTIFIER(ID).				{ A = new ParameterList(); A->addParameter(T, ID->getText()); }
params(A) ::= params(B) T_COMMA type(T) T_IDENTIFIER(ID).
													{ B->addParameter(T, ID->getText()); A = B; }

%type statement {Statement*}
statement(A) ::= T_IF T_LPAREN expr(E) T_RPAREN statement(S).
													{ A = new IfStatement(E, S); }
statement(A) ::= T_RIF T_LPAREN expr(P) T_RPAREN statement(S).
													{ A = new RandomIfStatement(P, S); }
statement(A) ::= T_FOR T_LPAREN statement(INIT) T_SEMICOLON expr(COND) T_SEMICOLON statement(STEP) T_RPAREN statement(S).
													{ A = new ForStatement(INIT, COND, STEP, S); }
statement(A) ::= T_RFOR T_LPAREN statement(INIT) T_SEMICOLON expr(P) T_SEMICOLON statement(STEP) T_RPAREN statement(S).
													{ A = new RandomForStatement(INIT, P, STEP, S); }
statement(A) ::= T_RETURN expr(E) T_SEMICOLON.		{ A = new ReturnStatement(E); }
statement(A) ::= T_BEGIN statements(S) T_END.		{ A = new Scope(S); }
statement(A) ::= vardef(V) T_SEMICOLON.				{ A = V; }
statement(A) ::= expr(E) T_SEMICOLON.				{ A = new ExpressionStatement(E); }

%type statements {StatementList*}
statements(A) ::= .									{ A = new StatementList(); }
statements(A) ::= statements(B) statement(C).		{ B->addStatement(C); A = B; }

%type expr {Expression*}
expr(A) ::= T_IDENTIFIER(ID).						{ A = new LoadExpression(ID->getText()); }
expr(A) ::= T_IDENTIFIER(ID) T_ASSIGN expr(E).		{ A = new AssignmentExpression(ID->getText(), E); }
expr(A) ::= expr(B) T_EQUALS expr(C).				{ A = new BinOpExpression(B, BinOp::EQUALS, C); }
expr(A) ::= expr(B) T_LESS expr(C).					{ A = new BinOpExpression(B, BinOp::LESS, C); }
expr(A) ::= expr(B) T_PLUS expr(C).					{ A = new BinOpExpression(B, BinOp::PLUS, C); }
expr(A) ::= expr(B) T_MINUS expr(C).				{ A = new BinOpExpression(B, BinOp::MINUS, C); }
expr(A) ::= expr(B) T_TIMES expr(C).				{ A = new BinOpExpression(B, BinOp::TIMES, C); }
expr(A) ::= expr(B) T_DIV expr(C).					{ A = new BinOpExpression(B, BinOp::DIV, C); }
expr(A) ::= T_CINT(I).								{ A = new ConstantExpression(I->getText()); }
expr(A) ::= T_TRUE.									{ A = new ConstantExpression("true"); }
expr(A) ::= T_FALSE.								{ A = new ConstantExpression("false"); }
expr(A) ::= T_IDENTIFIER(ID) T_LPAREN values(V) T_RPAREN.
													{ A = new FunctionCallExpression(ID->getText(), V); }

%type vardef {VariableDefinition*}
vardef(A) ::= type(T) T_IDENTIFIER(ID).				{ A = new VariableDefinition(T, ID->getText()); }

%type values {ValueList*}
values(A) ::= .										{ A = new ValueList(); }
values(A) ::= expr(E).								{ A = new ValueList(); A->addValue(E); }
values(A) ::= values(B) T_COMMA expr(E).			{ B->addValue(E); A = B; }

