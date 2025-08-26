#include"Lexer.h"

enum class TokenType { VAR, EQ, PLUS, MINUS, NUMBER, STRING, SEMICOLON, TAB, IF, END, COLON, NOT, IS_EQ, NOT_EQ, LEFT_BRACKET, RIGHT_BRACKET, IF_END, MULT, DIV, PRINT};
//std::string regexes[] = { "^[a-zA-Z_].*", "=", "\\+", "\\-", "[0-9]+" ".*", "	", "\""};

bool tab = false;

std::string TokenTypeSwitch(TokenType type)
{
	int int_type = static_cast<int>(type);
	switch (int_type)
	{
	case 0: return "VAR";
	case 1: return "EQ";
	case 2: return "PLUS";
	case 3: return "MINUS";
	case 4: return "NUMBER";
	case 5: return "STRING";
	case 6: return "SEMICOLON";
	case 7: return "TAB";
	case 8: return "IF";
	case 9: return "END";
	case 10: return "COLON";
	case 11: return "NOT";
	case 12: return "IS_EQ";
	case 13: return "NOT_EQ";
	case 14: return "LEFT_BRACKET";
	case 15: return "RIGHT_BRACKET";
	case 16: return "IF_END";
	case 17: return "MULT";
	case 18: return "DIV";
	case 19: return "PRINT";
	}
}


Lexer::Lexer(std::string _line) : line(_line) {}
Lexer::Lexer(){}

void Lexer::TokensSort()
{
	size_t tokens_size = tokens.size() - 1;
	if (tokens_size > 1)
	{
		for (size_t i = 1; i < tokens_size; ++i)
		{
			if (tokens[i]->type == TokenType::EQ && tokens[i - 1]->type == TokenType::EQ)
			{
				tokens.erase(tokens.begin() + i);
				tokens[i - 1]->value = "==";
				tokens[i - 1]->type = TokenType::IS_EQ;
			}
			if (tokens[i]->type == TokenType::EQ && tokens[i - 1]->type == TokenType::NOT)
			{
				tokens.erase(tokens.begin() + i);
				tokens[i - 1]->value = "!=";
				tokens[i - 1]->type = TokenType::NOT_EQ;
			}
		}
		
	}
}

void Lexer::parseNumber()
{
	std::string number;
	number += line[iter];
	++iter;
	char curent = line[iter];
	while (curent == '0' || curent == '1' || curent == '2' || curent == '3' || curent == '4' ||
		curent == '5' || curent == '6' || curent == '7' || curent == '8' || curent == '9')
	{
		number += line[iter];
		++iter;
		curent = line[iter];
	}
	tokens.push_back(new Token(TokenType::NUMBER, number));
}

void Lexer::parseString()
{
	std::string string;
	++iter;
	char curent = line[iter];
	while (curent != '\"')
	{
		string += curent;
		++iter;
	}
	tokens.push_back(new Token(TokenType::STRING, string));
}

void Lexer::parseVar()
{
	std::string var;
	char curent = line[iter];
	var += curent;
	++iter;
	curent = line[iter];
	bool done = false;
	bool not_end = false;
	while (1)
	{
		for (size_t i = 0; i < alf_size; ++i)
		{
			if (curent == alf[i])
			{
				var += curent;
				not_end = true;
				break;
			}
		}
		if (!not_end)
			break;
		++iter;
		curent = line[iter];
		not_end = false;
	}
	if(var == "if")
		tokens.push_back(new Token(TokenType::IF, var));
	else if(var == "print")
		tokens.push_back(new Token(TokenType::PRINT, var));
	else
		tokens.push_back(new Token(TokenType::VAR, var));
}

void Lexer::Analys()
{
	//std::regex regular(R"((^[a-zA-Z_].*|=|\\+|\\-|\\d+|^\".*\"$)|\t| )");
	if (line[0] != '\t' && tab == true) 
	{
		tab = false;
		tokens.push_back(new Token(TokenType::IF_END, ""));
	}
	char curent;

	line_size = line.size();

	while(1)
	{
		if (iter == line_size)
		{
			tokens.push_back(new Token(TokenType::END, ""));
			break;
		}
		curent = line[iter];
		if (curent == '=')
		{
			tokens.push_back(new Token(TokenType::EQ, "="));
			++iter;
		}
		else if (curent == ';') {
			tokens.push_back(new Token(TokenType::SEMICOLON, ";"));
			++iter;
		}
		else if (curent == '+'){
			tokens.push_back(new Token(TokenType::PLUS, "+"));
			++iter;
		}
		else if (curent == '-'){
			tokens.push_back(new Token(TokenType::MINUS, "-"));
			++iter;
		}
		else if (curent == '!') {
			tokens.push_back(new Token(TokenType::NOT, "!"));
			++iter;
		}
		else if(curent == ':') {
			tokens.push_back(new Token(TokenType::COLON, ":"));
			++iter;
		}
		else if(curent == '\t') {
			tokens.push_back(new Token(TokenType::TAB, ""));
			tab = true;
			++iter;
		}

		else if (curent == '0' || curent == '1' || curent == '2' || curent == '3' || curent == '4' ||
			curent == '5' || curent == '6' || curent == '7' || curent == '8' || curent == '9')
			parseNumber();
		else if (curent == '\"')
			parseString();
		else if (curent == ' ')
			++iter;
		else
		{
			bool is_var = false;
			for (size_t i = 0; i < fchar_size; ++i)
			{
				if (curent == fchar[i]) {
					parseVar();
					is_var = true;
					break;
				}
			}
			if (!is_var)
			{
				std::cout << "error in char: " << iter << "\n";
				std::cout << "char: " << line[iter] << "\n";
				return;
			}
		}

	}
	TokensSort();
	iter = 0;
}

void Lexer::printTokens()
{
	for (size_t i = 0; i < tokens.size(); ++i) 
	{
		std::cout << tokens[i]->value << "  " << TokenTypeSwitch(tokens[i]->type) << '\n';
	}
}

Token::Token(TokenType _type, std::string _value) : type(_type), value(_value) {}