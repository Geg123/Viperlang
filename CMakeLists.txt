cmake_minimum_required(VERSION 3.8)

project(Geg-interpretator)

add_executable(Interpretator
	src/main.cpp
	src/Lexer.cpp
	src/Parser.cpp
	src/Operators.cpp
	src/Creator.cpp
	src/ObjectManager.cpp
	src/Interpretator.cpp
)