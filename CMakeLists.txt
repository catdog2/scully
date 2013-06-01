# The scully programming language
#
# Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
# Licensed under the GNU GPL v2.

CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (scully)

SET (SCULLY_VERSION_MAJOR 0)
SET (SCULLY_VERSION_MINOR 2)
SET (SCULLY_VERSION_RELEASE 0)
SET (SCULLY_VERSION_EXTRA "WoC Caturday")

SET (CMAKE_MODULE_PATH  ${CMAKE_SOURCE_DIR}/cmake/)

INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR})

INCLUDE_DIRECTORIES (${CMAKE_SOURCE_DIR}/inc)

SET (CMAKE_CXX_FLAGS "-std=c++11")

ADD_EXECUTABLE (lemon grammar/lemon.c)
ADD_EXECUTABLE (makeheaders grammar/makeheaders.c)

ADD_CUSTOM_COMMAND(
	COMMAND cp
	ARGS ${CMAKE_CURRENT_SOURCE_DIR}/grammar/grammar.y ${CMAKE_CURRENT_BINARY_DIR}
	COMMAND cp
	ARGS ${CMAKE_CURRENT_SOURCE_DIR}/grammar/lempar.c ${CMAKE_CURRENT_BINARY_DIR}
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/lemon
	ARGS -q -m ${CMAKE_CURRENT_BINARY_DIR}/grammar.y
#	ARGS -q ${CMAKE_CURRENT_BINARY_DIR}/grammar.y
	COMMAND rm
	ARGS ${CMAKE_CURRENT_BINARY_DIR}/lempar.c
	COMMAND rm
	ARGS ${CMAKE_CURRENT_BINARY_DIR}/grammar.y
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/makeheaders
	ARGS ${CMAKE_CURRENT_BINARY_DIR}/grammar.c
	COMMAND mv
	ARGS ${CMAKE_CURRENT_BINARY_DIR}/grammar.c ${CMAKE_CURRENT_BINARY_DIR}/grammar.cpp
	DEPENDS lemon
	DEPENDS makeheaders
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/grammar/grammar.y
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/grammar.cpp
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/grammar.h
)

SET_SOURCE_FILES_PROPERTIES(
	${CMAKE_CURRENT_BINARY_DIR}/grammar.cpp GENERATED
)

OPTION (SCULLY_DEBUG "Create a debug build")
IF (SCULLY_DEBUG)
	ADD_DEFINITIONS ("-g")
ENDIF (SCULLY_DEBUG)


SET(SCULLY_SOURCE
	src/test.cpp

	src/Token.cpp

	src/AST/ASTElement.cpp
	src/AST/ASTVisitor.cpp
	src/AST/AssignmentExpression.cpp
	src/AST/BinOpExpression.cpp
	src/AST/CodeGenVisitor.cpp
	src/AST/ConstantExpression.cpp
	src/AST/LoadExpression.cpp
	src/AST/Expression.cpp
	src/AST/ExpressionStatement.cpp
	src/AST/ForStatement.cpp
	src/AST/FunctionCallExpression.cpp
	src/AST/FunctionDefinition.cpp
	src/AST/IfStatement.cpp
	src/AST/ParameterList.cpp
	src/AST/PrintVisitor.cpp
	src/AST/ReturnStatement.cpp
	src/AST/RandomForStatement.cpp
	src/AST/RandomIfStatement.cpp
	src/AST/Scope.cpp
	src/AST/Statement.cpp
	src/AST/StatementList.cpp
	src/AST/Type.cpp
	src/AST/VariableDefinition.cpp
	src/AST/ValueList.cpp
	src/AST/LoadExpression.cpp


	${CMAKE_CURRENT_BINARY_DIR}/grammar.cpp
)

FIND_PACKAGE (LLVM REQUIRED)
ADD_DEFINITIONS (${LLVM_CFLAGS})

ADD_EXECUTABLE (scully ${SCULLY_SOURCE})

TARGET_LINK_LIBRARIES (scully ${LLVM_JIT_LIBS})
TARGET_LINK_LIBRARIES (scully ${LLVM_LFLAGS})
