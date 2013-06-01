%include {

#include <cstdio>
#include <iostream>
#include <string>
#include <assert.h>

#include "Token.h"

#include "AST/ASTElement.h"
#include "AST/AssignmentExpression.h"
#include "AST/BinOp.h"
#include "AST/ConstantExpression.h"
#include "AST/Expression.h"
#include "AST/ParameterList.h"
#include "AST/Statement.h"
#include "AST/StatementList.h"
#include "AST/Type.h"
#include "AST/ValueList.h"
#include "AST/VariableDefinition.h"

}

%name scullyParser

%token_type {Token*}

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
program ::= fundefs(F).								{ std::cout << F << std::endl; }
program ::= expr(E).								{ std::cout << E << std::endl; }

%type fundefs {int}
fundefs(A) ::= .									{ A = 0; }
fundefs(A) ::= fundefs fundef(B).					{ A = A + B; }

%type fundef {int}
fundef(A) ::= type(T) T_IDENTIFIER(ID) T_LPAREN params(P) T_RPAREN T_BEGIN statements(S) T_END.
													{ A = 1 + 1 + 1 + S; /* T P ID */ }

%type type {Type*}
type(A) ::= T_BOOL.									{ A = new Type("bool"); }
type(A) ::= T_INT.									{ A = new Type("int"); }
type(A) ::= T_STRING.								{ A = new Type("string"); }
type(A) ::= T_VOID.									{ A = new Type("void"); }

%type params {ParameterList*}
params(A) ::= .										{ A = new ParameterList(); }
params(A) ::= type(T) T_IDENTIFIER(ID).				{ A = new ParameterList(); A->addParameter(T, ID->getText()); }
params(A) ::= params(B) T_COMMA type(T) T_IDENTIFIER(ID).
													{ B->addParameter(T, ID->getText()); A = B; }

%type statement {int}
statement(A) ::= T_IF T_LPAREN expr(E) T_RPAREN statement(S).
													{ A = 1 + S; /* E */ }
statement(A) ::= T_RIF T_LPAREN T_CINT(P) T_RPAREN statement(S).
													{ A = 1 + S; /* P */ }
statement(A) ::= T_FOR T_LPAREN expr(INIT) T_SEMICOLON expr(COND) T_SEMICOLON expr(STEP) T_RPAREN statement(S).
													{ A = 1 + 1 + 1 + S; /* INIT COND STEP */ }
statement(A) ::= T_RFOR T_LPAREN expr(INIT) T_SEMICOLON T_CINT(P) T_SEMICOLON expr(STEP) T_RPAREN statement(S).
													{ A = 1 + 1 + 1 + S; /* INIT P STEP */ }
statement(A) ::= T_RETURN expr(E) T_SEMICOLON.		{ A = 1; /* E */ }
statement(A) ::= T_BEGIN statements(S) T_END.		{ A = S; }
statement(A) ::= vardef(V) T_SEMICOLON.				{ A = 1; /* V */ }
statement(A) ::= expr(E) T_SEMICOLON.				{ A = 1; /* E */ }

%type statements {StatementList*}
statements(A) ::= .									{ A = new StatementList(); }
statements(A) ::= statements(B) statement(C).		{ B->addStatement(C); A = B; }

%type expr {Expression*}
expr(A) ::= T_IDENTIFIER(ID) T_ASSIGN expr(E).		{ A = new AssignmentExpression(ID->getText(), E); }
expr(A) ::= expr(B) T_EQUALS expr(C).				{ A = new BinOp(B, "==", C); }
expr(A) ::= expr(B) T_LESS expr(C).					{ A = new BinOp(B, "<", C); }
expr(A) ::= expr(B) T_PLUS expr(C).					{ A = new BinOp(B, "+", C); }
expr(A) ::= expr(B) T_MINUS expr(C).				{ A = new BinOp(B, "-", C); }
expr(A) ::= expr(B) T_TIMES expr(C).				{ A = new BinOp(B, "*", C); }
expr(A) ::= expr(B) T_DIV expr(C).					{ A = new BinOp(B, "/", C); }
expr(A) ::= T_CINT(I).								{ A = new ConstantExpression(I->getText()); }
expr(A) ::= T_TRUE.									{ A = new ConstantExpression("true"); }
expr(A) ::= T_FALSE.								{ A = new ConstantExpression("false"); }
expr(A) ::= T_IDENTIFIER(ID) T_LPAREN values(V) T_RPAREN.
													{ A = 0; /* ID V */ }

%type vardef {VariableDefinition*}
vardef(A) ::= type(T) T_IDENTIFIER(ID).				{ A = new VariableDefinition(T, ID->getText()); }

%type values {ValueList*}
values(A) ::= .										{ A = new ValueList(); }
values(A) ::= expr(E).								{ A = new ValueList(); A->addValue(E); }
values(A) ::= values(B) T_COMMA expr(E).			{ B->addValue(E); A = B; }

