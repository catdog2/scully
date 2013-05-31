%include {

#include <iostream>
#include <string>
#include <assert.h>

}

%token_type {int}

%left PLUS MINUS.

%syntax_error {
    std::cout << "Syntax error!" << std::endl;
}

program ::= expr.            { }

expr ::= expr PLUS expr.     { }
