#pragma once
#include<string>
#include<vector>
#include<iostream>

enum class TokenType { VAR, EQ, PLUS, MINUS, NUMBER, STRING, SEMICOLON, TAB,
	IF, END, COLON, NOT, IS_EQ, NOT_EQ, LEFT_BRACKET, RIGHT_BRACKET,
	IF_END, MULT, DIV, PRINT, COMMA, ARRAY, SQ_LEFT_BRACKET, SQ_RIGHT_BRACKET,
	ARR_LIST, BOOL, TRUE, FALSE, GREATER, LESS, AND, OR, FUNCTION, POINT,
	RETURN, FUNC_END, FUNC_INIT, INPUT, INT, MODULE,
	FOR, FOR_END, IN, RANGE
};


std::string TokenTypeSwitch(TokenType type);
TokenType StringToTokenType(std::string type);

struct Token
{
	Token(TokenType _type, std::string _value);

	TokenType type;
	std::string value;
};

struct Lexer
{
	Lexer(std::string _line);
	Lexer();
	void parseNumber();
	void parseString();
	void parseVar();
	void Analys();
	void TokensSort();
	void printTokens();

	std::vector<std::shared_ptr<Token>> tokens;
	std::string line;
	int iter = 0;
	size_t line_size;
	const char fchar[53] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char alf[64] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890";
	size_t fchar_size = 52;
	size_t alf_size = 63;
};

struct VarToken;

struct OperatorToken;

struct ValueToken;