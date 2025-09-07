#pragma once
#include"Lexer.h"

struct NodeAST
{
	NodeAST(std::shared_ptr<Token> _token);
	std::shared_ptr<Token> token = nullptr;
	std::shared_ptr<NodeAST> left = nullptr;
	std::shared_ptr<NodeAST> right = nullptr;
};

struct AST
{
	AST(Lexer* _lexer);
	//void parseMultAndDiv(size_t& iter);
	//void parseBrackets(size_t& iter);
	//void parsePlusAndMinus(size_t& iter);
	std::shared_ptr<NodeAST> parseMathExpr(size_t iter, size_t end_iter);
	std::shared_ptr<NodeAST> parseStringExpr(size_t iter, size_t end_iter);
	std::shared_ptr<NodeAST> parseVarExpr(size_t iter, size_t end_iter);
	std::shared_ptr<NodeAST> parsePrint(size_t iter, size_t end_iter);
	std::shared_ptr<NodeAST> parseIF(size_t iter, size_t end_iter);
	std::shared_ptr<NodeAST> parseArray(size_t iter, size_t end_iter);
	std::shared_ptr<NodeAST> parseArrayIndex(size_t i);
	std::shared_ptr<NodeAST> parseBool(size_t iter, size_t end_iter);
	void Analys();

	std::vector<std::shared_ptr<NodeAST>> line_nodes;
	//здесь лежат все ноды, то есть все строку только в виде деревьев ast

	Lexer* lexer;
};
