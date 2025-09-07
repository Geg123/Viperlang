#include"../include/Lexer.h"

enum class TokenType { VAR, EQ, PLUS, MINUS, NUMBER, STRING, SEMICOLON, TAB, IF, END, COLON, NOT, IS_EQ, NOT_EQ, LEFT_BRACKET, RIGHT_BRACKET, IF_END, MULT, DIV, PRINT, COMMA, ARRAY, SQ_LEFT_BRACKET, SQ_RIGHT_BRACKET, ARR_LIST, BOOL, TRUE, FALSE, GREATER, LESS, AND, OR, FUNCTION};
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
	case 20: return "COMMA";
	case 21: return "ARRAY";
	case 22: return "SQ_LEFT_BRACKET";
	case 23: return "SQ_RIGHT_BRACKET";
	case 24: return "ARR_LIST";
	case 25: return "BOOL";
	case 26: return "TRUE";
	case 27: return "FALSE";
	case 28: return "GREATER";
	case 29: return "LESS";
	case 30: return "AND";
	case 31: return "OR";
	}
}


TokenType StringToTokenType(std::string type)
{

	if (type == "VAR")
		return TokenType::VAR;
	else if(type == "EQ")
		return TokenType::EQ;
	else if (type == "PLUS")
		return TokenType::PLUS;
	else if (type == "MINUS")
		return TokenType::MINUS;
	else if (type == "NUMBER")
		return TokenType::NUMBER;
	else if (type == "STRING")
		return TokenType::STRING;
	else if (type == "SEMICOLON")
		return TokenType::SEMICOLON;
	else if (type == "TAB")
		return TokenType::TAB;
	else if (type == "IF")
		return TokenType::IF;
	else if (type == "END")
		return TokenType::END;
	else if (type == "COLON")
		return TokenType::COLON;
	else if (type == "NOT")
		return TokenType::NOT;
	else if (type == "IS_EQ")
		return TokenType::IS_EQ;
	else if (type == "NOT_EQ")
		return TokenType::NOT_EQ;
	else if (type == "LEFT_BRACKET")
		return TokenType::LEFT_BRACKET;
	else if (type == "RIGHT_BRACKET")
		return TokenType::RIGHT_BRACKET;
	else if (type == "IF_END")
		return TokenType::IF_END;
	else if (type == "MULT")
		return TokenType::MULT;
	else if (type == "DIV")
		return TokenType::DIV;
	else if (type == "PRINT")
		return TokenType::PRINT;
	else if (type == "COMMA")
		return TokenType::COMMA;
	else if (type == "ARRAY")
		return TokenType::ARRAY;
	else if (type == "SQ_LEFT_BRACKET")
		return TokenType::SQ_LEFT_BRACKET;
	else if (type == "SQ_RIGHT_BRACKET")
		return TokenType::SQ_RIGHT_BRACKET;
	else if (type == "ARR_LIST")
		return TokenType::ARR_LIST;
	else if (type == "BOOL")
		return TokenType::BOOL;
	else if (type == "TRUE")
		return TokenType::TRUE;
	else if (type == "FALSE")
		return TokenType::FALSE;
	else if (type == "GREATER")
		return TokenType::GREATER;
	else if (type == "LESS")
		return TokenType::LESS;
	else if (type == "AND")
		return TokenType::AND;
	else if (type == "OR")
		return TokenType::OR;
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
			else if (tokens[i]->type == TokenType::EQ && tokens[i - 1]->type == TokenType::NOT)
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
	char current = line[iter];
	while (current == '0' || current == '1' || current == '2' || current == '3' || current == '4' ||
		current == '5' || current == '6' || current == '7' || current == '8' || current == '9')
	{
		number += line[iter];
		++iter;
		current = line[iter];
	}
	tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, number));
}

void Lexer::parseString()
{
	std::string string;
	++iter;
	char current = line[iter];
	while (current != '\"')
	{
		string += current;
		++iter;
		current = line[iter];
	}
	tokens.push_back(std::make_shared<Token>(TokenType::STRING, string));
	++iter;
}

void Lexer::parseVar()
{
	std::string var;
	char current = line[iter];
	var += current;
	++iter;
	current = line[iter];
	bool done = false;
	bool not_end = false;
	while (1)
	{
		for (size_t i = 0; i < alf_size; ++i)
		{
			if (current == alf[i])
			{
				var += current;
				not_end = true;
				break;
			}
		}
		if (!not_end)
			break;
		++iter;
		current = line[iter];
		not_end = false;
	}
	if(var == "if")
		tokens.push_back(std::make_shared<Token>(TokenType::IF, var));
	else if(var == "print")
		tokens.push_back(std::make_shared<Token>(TokenType::PRINT, var));
	else if (var == "true")
		tokens.push_back(std::make_shared<Token>(TokenType::TRUE, var));
	else if (var == "false")
		tokens.push_back(std::make_shared<Token>(TokenType::FALSE, var));
	else if (var == "and")
		tokens.push_back(std::make_shared<Token>(TokenType::AND, var));
	else if (var == "or")
		tokens.push_back(std::make_shared<Token>(TokenType::OR, var));
	else
		tokens.push_back(std::make_shared<Token>(TokenType::VAR, var));
}

void Lexer::Analys()
{
	//std::regex regular(R"((^[a-zA-Z_].*|=|\\+|\\-|\\d+|^\".*\"$)|\t| )");
	if (line[0] != '\t' && tab == true) 
	{
		tab = false;
		tokens.push_back(std::make_shared<Token>(TokenType::IF_END, ""));
	}
	char current;

	line_size = line.size();

	while(1)
	{
		if (iter == line_size)
		{
			tokens.push_back(std::make_shared<Token>(TokenType::END, ""));
			break;
		}
		current = line[iter];
		if (current == '=')
		{
			tokens.push_back(std::make_shared<Token>(TokenType::EQ, "="));
			++iter;
		}
		else if (current == ';') {
			tokens.push_back(std::make_shared<Token>(TokenType::SEMICOLON, ";"));
			++iter;
		}
		else if (current == '+'){
			tokens.push_back(std::make_shared<Token>(TokenType::PLUS, "+"));
			++iter;
		}
		else if (current == '-'){
			tokens.push_back(std::make_shared<Token>(TokenType::MINUS, "-"));
			++iter;
		}
		else if(current =='*') {
			tokens.push_back(std::make_shared<Token>(TokenType::MULT, "*"));
			++iter;
		}
		else if (current == '!') {
			tokens.push_back(std::make_shared<Token>(TokenType::NOT, "!"));
			++iter;
		}
		else if(current == ':') {
			tokens.push_back(std::make_shared<Token>(TokenType::COLON, ":"));
			++iter;
		}
		else if(current == '\t') {
			tokens.push_back(std::make_shared<Token>(TokenType::TAB, ""));
			tab = true;
			++iter;
		}
		else if (current == '(') {
			tokens.push_back(std::make_shared<Token>(TokenType::LEFT_BRACKET, "("));
			++iter;
		}
		else if (current == ')') {
			tokens.push_back(std::make_shared<Token>(TokenType::RIGHT_BRACKET, ")"));
			++iter;
		}
		else if (current == '[') {
			tokens.push_back(std::make_shared<Token>(TokenType::SQ_LEFT_BRACKET, "["));
			++iter;
		}
		else if (current == ']') {
			tokens.push_back(std::make_shared<Token>(TokenType::SQ_RIGHT_BRACKET, "]"));
			++iter;
		}
		else if (current == ',') {
			tokens.push_back(std::make_shared<Token>(TokenType::COMMA, ","));
			++iter;
		}
		else if (current == '>')
		{
			tokens.push_back(std::make_shared<Token>(TokenType::GREATER, ">"));
			++iter;
		}
		else if (current == '<')
		{
			tokens.push_back(std::make_shared<Token>(TokenType::LESS, "<"));
			++iter;
		}
		else if (current == '0' || current == '1' || current == '2' || current == '3' || current == '4' ||
			current == '5' || current == '6' || current == '7' || current == '8' || current == '9')
			parseNumber();
		else if (current == '\"')
			parseString();
		else if (current == ' ')
			++iter;
		else
		{
			bool is_var = false;
			for (size_t i = 0; i < fchar_size; ++i)
			{
				if (current == fchar[i]) {
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