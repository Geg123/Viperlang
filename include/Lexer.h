#pragma once

#include<string>
#include<vector>
#include<iostream>

enum class TokenType;


std::string TokenTypeSwitch(TokenType type);

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

	const char fchar[53] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char alf[64] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890";

	size_t fchar_size = 52;
	size_t alf_size = 63;

	void parseNumber();
	void parseString();
	void parseVar();
	void Analys();
	void TokensSort();
	std::vector<Token*> tokens;
	std::string line;
	int iter = 0;
	size_t line_size;
	void printTokens();
};

struct VarToken;

struct OperatorToken;

struct ValueToken;