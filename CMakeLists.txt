cmake_minimum_required(VERSION 3.8)

project(Viper interpretator)

add_executable(Compiler 
	src/main.cpp
	src/Lexer.cpp
	src/AST.cpp
	src/Var.cpp
	src/Array.cpp
	src/Interpretator.cpp
	src/Func.cpp
)