cmake_minimum_required(VERSION 3.8)

project(Compiler)

add_executable(Compiler 
	src/main.cpp
	src/Lexer.cpp
	src/AST.cpp
)