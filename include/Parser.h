#pragma once
#include"Lexer.h"

struct NodeAST
{
	NodeAST(std::shared_ptr<Token> _token);

	std::shared_ptr<Token> token = nullptr;
	std::shared_ptr<NodeAST> left = nullptr;
	std::shared_ptr<NodeAST> right = nullptr;
};

struct Parser
{
	Parser(){}
	void ParserLexerInit(Lexer* _lexer);
	std::shared_ptr<NodeAST> parseExpr(size_t iter, size_t end_iter);
	std::shared_ptr<NodeAST> parseIF(size_t iter, size_t end_iter);
	std::shared_ptr<NodeAST> parseArray(size_t iter, size_t end_iter);
	std::shared_ptr<NodeAST> parseArrayIndex(size_t i);
	std::shared_ptr<NodeAST> parseFuncInit(size_t iter, size_t end_iter);
	std::shared_ptr<NodeAST> parseFor(size_t iter, size_t end_iter);
	void Analys();

	std::vector<std::shared_ptr<NodeAST>> line_nodes;
	std::shared_ptr<Lexer> lexer;
};
