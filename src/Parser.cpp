#include"../include/Parser.h"

NodeAST::NodeAST(std::shared_ptr<Token> _token) : token(_token) {}

void Parser::ParserLexerInit(Lexer* _lexer)
{
	lexer = std::make_shared<Lexer>(*_lexer);
}

std::shared_ptr<NodeAST> Parser::parseExpr(size_t iter, size_t end_iter)
{
	std::vector<std::shared_ptr<NodeAST>> nodes;

	bool mult = false;
	bool plus = false;
	bool more = false;
	bool is_eq = false;
	bool and = false;
	bool or = false;
	bool input = false;
	bool power = false;

	for (size_t i = iter; i < end_iter; ++i)
	{
		TokenType type =lexer->tokens[i]->type;

		if (type == TokenType::MULT)
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			mult = true;
		}
		else if (type == TokenType::DIV)
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			mult = true;
		}
		else if (type == TokenType::MODULE)
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			mult = true;
		}
		else if (type == TokenType::INPUT)
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			int brackets_pares = 0;
			size_t j = i + 2;
			if (lexer->tokens[i + 1]->type == TokenType::LEFT_BRACKET) {
				while (1)
				{
					if (lexer->tokens[j]->type == TokenType::LEFT_BRACKET)
						++brackets_pares;
					else if (lexer->tokens[j]->type == TokenType::RIGHT_BRACKET && brackets_pares != 0)
						--brackets_pares;
					else if (lexer->tokens[j]->type == TokenType::RIGHT_BRACKET && brackets_pares == 0)
						break;
					++j;
				}
				//nodes.push_back(parseExpr(i + 2, j));
				if (j != i + 2)
				{
					nodes[nodes.size() - 1]->right = parseExpr(i + 2, j);
				}
				i = j;
			}
			//input = true;
			else
			{
				std::cout << "Error: expected \"(\" after \"input\"!\n";
				system("pause");
			}
		}
		else if (type == TokenType::INT)
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			int brackets_pares = 0;
			size_t j = i + 2;
			if (lexer->tokens[i + 1]->type == TokenType::LEFT_BRACKET) {
				while (1)
				{
					if (lexer->tokens[j]->type == TokenType::LEFT_BRACKET)
						++brackets_pares;
					else if (lexer->tokens[j]->type == TokenType::RIGHT_BRACKET && brackets_pares != 0)
						--brackets_pares;
					else if (lexer->tokens[j]->type == TokenType::RIGHT_BRACKET && brackets_pares == 0)
						break;
					++j;
				}
				//nodes.push_back(parseExpr(i + 2, j));
				if (j != i + 2)
				{
					nodes[nodes.size() - 1]->right = parseExpr(i + 2, j);
				}
				i = j;
			}
			//input = true;
			else
			{
				std::cout << "Error: expected \"(\" after \"int\"!\n";
				system("pause");
			}
		}
		else if (type == TokenType::VAR)
		{
			if (lexer->tokens[i]->value == "input")
			{
				nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
				int brackets_pares = 0;
				size_t j = i + 2;
				if (lexer->tokens[i + 1]->type == TokenType::LEFT_BRACKET) {
					while (1)
					{
						if (lexer->tokens[j]->type == TokenType::LEFT_BRACKET)
							++brackets_pares;
						else if (lexer->tokens[j]->type == TokenType::RIGHT_BRACKET && brackets_pares != 0)
							--brackets_pares;
						else if (lexer->tokens[j]->type == TokenType::RIGHT_BRACKET && brackets_pares == 0)
							break;
						++j;
					}
					//nodes.push_back(parseExpr(i + 2, j));
					if (j != i + 2)
					{
						nodes[nodes.size() - 1]->right = parseExpr(i + 2, j);
					}
					i = j;
				}
				//input = true;
				else
				{
					std::cout << "Error: expected \"(\" after \"input\"!\n";
					system("pause");
				}
			}
			else if (lexer->tokens[i]->value == "int")
			{
				nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
				int brackets_pares = 0;
				size_t j = i + 2;
				if (lexer->tokens[i + 1]->type == TokenType::LEFT_BRACKET) {
					while (1)
					{
						if (lexer->tokens[j]->type == TokenType::LEFT_BRACKET)
							++brackets_pares;
						else if (lexer->tokens[j]->type == TokenType::RIGHT_BRACKET && brackets_pares != 0)
							--brackets_pares;
						else if (lexer->tokens[j]->type == TokenType::RIGHT_BRACKET && brackets_pares == 0)
							break;
						++j;
					}
					//nodes.push_back(parseExpr(i + 2, j));
					if (j != i + 2)
					{
						nodes[nodes.size() - 1]->right = parseExpr(i + 2, j);
					}
					i = j;
				}
				//input = true;
				else
				{
					std::cout << "Error: expected \"(\" after \"int\"!\n";
					system("pause");
				}
			}
			else if(lexer->tokens[i + 1]->type == TokenType::SQ_LEFT_BRACKET)
			{
				int brackets_pares = 0;
				size_t j = i + 2;
				while (1)
				{
					if (lexer->tokens[j]->type == TokenType::SQ_LEFT_BRACKET)
						++brackets_pares;
					else if (lexer->tokens[j]->type == TokenType::SQ_RIGHT_BRACKET && brackets_pares != 0)
						--brackets_pares;
					else if (lexer->tokens[j]->type == TokenType::SQ_RIGHT_BRACKET && brackets_pares == 0)
						break;
					++j;
				}
				nodes.push_back(parseArrayIndex(j));
				i = j;
			}
			else if (lexer->tokens[i + 1]->type == TokenType::LEFT_BRACKET)
			{
				lexer->tokens[i]->type = TokenType::FUNCTION;
				nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));

				size_t current = i;
				size_t curr_end = current;

				std::shared_ptr<NodeAST> tmp = nodes[nodes.size() - 1];

				current += 2;

				size_t l_brac = 0;
				size_t k = current;
				while (1)
				{
					if (lexer->tokens[k]->type == TokenType::LEFT_BRACKET)
						++l_brac;
					else if (lexer->tokens[k]->type == TokenType::RIGHT_BRACKET && l_brac != 0)
						--l_brac;
					else if (lexer->tokens[k]->type == TokenType::RIGHT_BRACKET && l_brac == 0)
						break;
					++k;
				}
				while (1)
				{
					bool found_right = false;
					for (size_t j = current; lexer->tokens[j]->type != TokenType::COMMA && j < k; ++j)
					{
						if (lexer->tokens[j]->type == TokenType::NUMBER)
						{
							found_right = true;
						}
						else if (lexer->tokens[j]->type == TokenType::STRING)
						{
							found_right = true;
						}
						else if (lexer->tokens[j]->type == TokenType::BOOL)
						{
							found_right = true;
						}
						else if (lexer->tokens[j]->type == TokenType::VAR)
						{
							found_right = true;
						}
						curr_end = j;
					}

					++curr_end;

					if (found_right)
					{
						tmp->left = std::make_shared<NodeAST>(std::make_shared<Token>(TokenType::FUNCTION, "node"));
						tmp->left->right = parseExpr(current, curr_end);
					}

					current = ++curr_end;
					//lexer->tokens[current]->type != TokenType::COMMA
					if (lexer->tokens[current - 1]->type != TokenType::RIGHT_BRACKET || lexer->tokens[current]->type == TokenType::COMMA)
						tmp = tmp->left;
					else
					{
						break;
					}
				}
				i = current;
			}
			else
				nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
		}
		else if (type == TokenType::NUMBER)
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
		else if (type == TokenType::STRING)
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
		else if (type == TokenType::TRUE)
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
		else if (type == TokenType::FALSE)
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
		else if (type == TokenType::PLUS)
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			plus = true;
		}
		else if (type == TokenType::MINUS)
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			plus = true;
		}
		else if (type == TokenType::GREATER)
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			more = true;
		}
		else if (type == TokenType::LESS)
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			more = true;
		}
		else if (type == TokenType::IS_EQ)
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			is_eq = true;
		}
		else if (type == TokenType::NOT_EQ)
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			is_eq = true;
		}
		else if (type == TokenType::AND)
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			and = true;
		}
		else if (type == TokenType::OR)
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			or = true;
		}
		else if(type == TokenType::POWER)
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			power = true;
		}
		else if (type == TokenType::LEFT_BRACKET)
		{
			int brackets_pares = 0;
			size_t j = i + 1;
			while (1)
			{
				if (lexer->tokens[j]->type == TokenType::LEFT_BRACKET)
					++brackets_pares;
				else if (lexer->tokens[j]->type == TokenType::RIGHT_BRACKET && brackets_pares != 0)
					--brackets_pares;
				else if (lexer->tokens[j]->type == TokenType::RIGHT_BRACKET && brackets_pares == 0)
					break;
				++j;
			}
			nodes.push_back(parseExpr(i + 1, j));
			i = j;
		}
		else if(type == TokenType::SQ_LEFT_BRACKET)
		{
			size_t l_sqbrac = 0;
			size_t k = ++i;
			while (1)
			{
			if (lexer->tokens[k]->type == TokenType::SQ_LEFT_BRACKET)
				++l_sqbrac;
			else if (lexer->tokens[k]->type == TokenType::SQ_RIGHT_BRACKET && l_sqbrac != 0)
				--l_sqbrac;
			else if (lexer->tokens[k]->type == TokenType::SQ_RIGHT_BRACKET && l_sqbrac == 0)
				break;
			++k;
			}
			nodes.push_back(parseArray(i, k));
			i = k;
		}
	}
	if(power)
	{
		size_t i = nodes.size() - 1;
		while (i >= 1 && i != 18446744073709551615)
		{
			if (nodes[i]->token->type == TokenType::POWER)
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			--i;
		}
	}
	if (mult)
	{
		size_t i = nodes.size() - 1;
		while (i >= 1 && i != 18446744073709551615)
		{
			if (nodes[i]->token->type == TokenType::MULT)
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			else if (nodes[i]->token->type == TokenType::DIV)
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			else if (nodes[i]->token->type == TokenType::MODULE)
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			--i;
		}
	}
	if (plus)
	{
		size_t i = nodes.size() - 1;
		while (i >= 1 && i != 18446744073709551615)
		{
			if (nodes[i]->token->type == TokenType::PLUS)
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			else if (nodes[i]->token->type == TokenType::MINUS)
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			--i;
		}
	}
	if (more)
	{
		size_t i = nodes.size() - 1;
		while (i >= 1 && i != 18446744073709551615)
		{
			if (nodes[i]->token->type == TokenType::GREATER)
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			else if (nodes[i]->token->type == TokenType::LESS)
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			--i;
		}
	}
	if (is_eq)
	{
		size_t i = nodes.size() - 1;
		while (i >= 1 && i != 18446744073709551615)
		{
			if (nodes[i]->token->type == TokenType::IS_EQ)
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			else if (nodes[i]->token->type == TokenType::NOT_EQ)
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			--i;
		}
	}
	if (and)
	{
		size_t i = nodes.size() - 1;
		while (i >= 1 && i != 18446744073709551615)
		{
			if (nodes[i]->token->type == TokenType::AND)
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			--i;
		}
	}
	if (or)
	{
		size_t i = nodes.size() - 1;
		while (i >= 1 && i != 18446744073709551615)
		{
			if (nodes[i]->token->type == TokenType::OR)
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			--i;
		}
	}
	return nodes[0];
}

std::shared_ptr<NodeAST> Parser::parseIF(size_t iter, size_t end_iter) 
{
	return nullptr;
}

std::shared_ptr<NodeAST> Parser::parseArray(size_t iter, size_t end_iter)
{
	std::shared_ptr<NodeAST> root = std::make_shared<NodeAST>(std::make_shared<Token>(TokenType::ARR_LIST,"root"));
	//zsize_t node_iter = 0;
	size_t current = iter;
	size_t curr_end;
	size_t index = 0;
	root->left = std::make_shared<NodeAST>(std::make_shared<Token>(TokenType::ARR_LIST, std::to_string(index)));
	std::shared_ptr<NodeAST> node = root->left;
	size_t l_sqbrac = 0;
	size_t k = current;
	while (1)
	{
		if (lexer->tokens[k]->type == TokenType::SQ_LEFT_BRACKET)
			++l_sqbrac;
		else if (lexer->tokens[k]->type == TokenType::SQ_RIGHT_BRACKET && l_sqbrac != 0)
			--l_sqbrac;
		else if (lexer->tokens[k]->type == TokenType::SQ_RIGHT_BRACKET && l_sqbrac == 0)
			break;
		++k;
	}
	while (1)
	{
		bool found_right = false;
		for (size_t j = current ; lexer->tokens[j]->type != TokenType::COMMA && j < k; ++j)
		{
			if (lexer->tokens[j]->type == TokenType::NUMBER)
			{
				found_right = true;
			}
			else if (lexer->tokens[j]->type == TokenType::STRING)
			{
				found_right = true;
			}
			else if (lexer->tokens[j]->type == TokenType::VAR)
			{
				found_right = true;
			}
			else if (lexer->tokens[j]->type == TokenType::BOOL)
			{
				found_right = true;
			}
			curr_end = j;
		}

		++curr_end;

		if (!found_right)
		{
			std::cout << "Element of array must be variable or number or string";
			system("pause");
		}
		node->right = parseExpr(current, curr_end);

		current = ++curr_end;

		if (current <= k)
		{
			node->left = std::make_shared<NodeAST>(std::make_shared<Token>(TokenType::ARR_LIST, std::to_string(++index)));
			node = node->left;
		}
		else
			break;
	}
	return root;
}


std::shared_ptr<NodeAST> Parser::parseArrayIndex(size_t right_bracket)
{
	std::shared_ptr<NodeAST> root;

	size_t end_iter = right_bracket - 1;
	size_t start_iter = end_iter;
	while (lexer->tokens[start_iter]->type != TokenType::SQ_LEFT_BRACKET && lexer->tokens[start_iter]->type != TokenType::END)
	{
		--start_iter;
	}

	++start_iter;

	if (lexer->tokens[start_iter]->type == TokenType::VAR || lexer->tokens[start_iter]->type == TokenType::NUMBER && lexer->tokens[end_iter]->type != TokenType::SQ_LEFT_BRACKET)
	{
		root = std::make_shared<NodeAST>(lexer->tokens[start_iter - 2]);
		root->token->type = TokenType::ARRAY;
		root->right = parseExpr(start_iter, end_iter + 1);
		return root;
	}
	else
	{
		std::cout << "Error: array index output must be arr[index]\n";
		system("pause");
	}
}

std::shared_ptr<NodeAST> Parser::parseFuncInit(size_t iter, size_t end_iter)
{
	std::shared_ptr<NodeAST> nodes = std::make_shared<NodeAST>(lexer->tokens[iter - 2]);
	std::shared_ptr<NodeAST> res = nodes;

	size_t current = iter;
	size_t curr_end = current;

	while (1)
	{
		bool found_right = false;

		for (size_t j = current; lexer->tokens[j]->type != TokenType::COMMA && lexer->tokens[j]->type != TokenType::RIGHT_BRACKET; ++j)
		{
			if (lexer->tokens[j]->type == TokenType::NUMBER)
			{
				found_right = true;
			}
			else if (lexer->tokens[j]->type == TokenType::STRING)
			{
				found_right = true;
			}
			else if (lexer->tokens[j]->type == TokenType::BOOL)
			{
				found_right = true;
			}
			else if (lexer->tokens[j]->type == TokenType::VAR)
			{
				found_right = true;
			}
			curr_end = j;
		}

		++curr_end;

		if (found_right)
		{
			//std::cout << "Element of function must be variable or number or string or bool";
			//system("pause");

			nodes->right = parseExpr(current, curr_end);
		}
		current = ++curr_end;
		if (current < end_iter)
			nodes = nodes->right;
		else
			break;
	}
	return res;
}

std::shared_ptr<NodeAST> Parser::parseFor(size_t iter, size_t end_iter)
{
	std::shared_ptr<NodeAST> root = std::make_shared<NodeAST>(lexer->tokens[iter - 1]);

	if (lexer->tokens[iter]->type == StringToTokenType("VAR"))
	{
		root->left = std::make_shared<NodeAST>(lexer->tokens[iter]);

		if (lexer->tokens[iter + 1]->type == StringToTokenType("IN") && lexer->tokens[iter + 2]->type == StringToTokenType("RANGE") && lexer->tokens[iter + 3]->type == StringToTokenType("LEFT_BRACKET"))
		{
			root->right = parseExpr(iter + 4, end_iter - 1);
			return root;
		}
	}
}

void Parser::Analys()
{
	std::shared_ptr<NodeAST> root;
	size_t tokens_size = lexer->tokens.size();

	size_t end_iter;

	bool last_end = false;
	

	for (size_t i = 0; i < tokens_size; ++i)
	{
		TokenType type = lexer->tokens[i]->type;
		size_t tabs = 0;
		if (type == TokenType::END)
		{
			continue;
		}
		for (; lexer->tokens[i]->type == TokenType::TAB; ++tabs, ++i){}
		type = lexer->tokens[i]->type;

		size_t size = tabs_stack.size();
		if (tabs < size)
		{
			while(tabs != size)
			{
				TokenType top = tabs_stack.top();
				if(top == TokenType::IF)
				{
					root = std::make_shared<NodeAST>(std::make_shared<Token>(TokenType::IF_END, ""));
					line_nodes.push_back(root);
				}
				else if(top == TokenType::FUNC_INIT)
				{
					root = std::make_shared<NodeAST>(std::make_shared<Token>(TokenType::FUNC_END, ""));
					line_nodes.push_back(root);
				}
				else if(top == TokenType::FOR)
				{
					root = std::make_shared<NodeAST>(std::make_shared<Token>(TokenType::FOR_END, ""));
					line_nodes.push_back(root);
				}
				tabs_stack.pop();
				size = tabs_stack.size();
			}
		}

		if (type == TokenType::EQ)
		{
			bool found_right = false;
			bool ArrDef = false;
			bool If = false;

			root = std::make_shared<NodeAST>(lexer->tokens[i]);
			if (lexer->tokens[i - 1]->type == TokenType::VAR)
				root->left = std::make_shared<NodeAST>(lexer->tokens[i - 1]);
			else if (lexer->tokens[i - 1]->type == TokenType::SQ_RIGHT_BRACKET)
			{
				root->left = parseArrayIndex(i - 1);
			}
			else
				throw "Left operand of \"=\" must be variable";
			for (size_t j = i + 1; lexer->tokens[j]->type != TokenType::END; ++j)
			{
				TokenType tmp =  lexer->tokens[j]->type;
				if (lexer->tokens[j]->type == TokenType::SQ_LEFT_BRACKET && lexer->tokens[j - 1]->type == TokenType::EQ)
				{
					found_right = true;
					ArrDef = true;
				}
				else if (tmp == TokenType::NUMBER || tmp == TokenType::STRING || tmp == TokenType::VAR || tmp == TokenType::BOOL || tmp == TokenType::FALSE || tmp == TokenType::TRUE || tmp == TokenType::INPUT)
				{
					found_right = true;
				}
				else if (lexer->tokens[j]->type == TokenType::IF)
				{

					found_right = true;
					If = true;
				}
				end_iter = j + 1;
			}


			if (!found_right)
				throw "Right operand of \"=\" must be variable or number or string";
			if (ArrDef)
				root->right = parseArray(i + 2, end_iter);
			if (If)
				root->right = parseIF(i + 2, end_iter);
			/*else if (Bool)
				root->right = parseBool(i + 1, end_iter);
			else if (Num && Str)
				root->right = parseStringExpr(i + 1, end_iter);
			else if (Var && Num)
				root->right = parseMathExpr(i + 1, end_iter);
			else if (Var && Str)
				root->right = parseStringExpr(i + 1, end_iter);
			else if (Num)
				root->right = parseMathExpr(i + 1, end_iter);
			else if (Str)
				root->right = parseStringExpr(i + 1, end_iter);
				*/
			else
				root->right = parseExpr(i + 1, end_iter);
			i = end_iter;

			line_nodes.push_back(root);
		}
		else if (type == TokenType::VAR && lexer->tokens[i + 1]->type == TokenType::EQ)
		{
			++i;
			bool found_right = false;
			bool If = false;

			root = std::make_shared<NodeAST>(lexer->tokens[i]);
			if (lexer->tokens[i - 1]->type == TokenType::VAR)
				root->left = std::make_shared<NodeAST>(lexer->tokens[i - 1]);
			else if (lexer->tokens[i - 1]->type == TokenType::SQ_RIGHT_BRACKET)
			{
				root->left = parseArrayIndex(i - 1);
			}
			else
				throw "Left operand of \"=\" must be variable";
			for (size_t j = i + 1; lexer->tokens[j]->type != TokenType::END; ++j)
			{
				TokenType tmp = lexer->tokens[j]->type;
				if (tmp == TokenType::NUMBER || tmp == TokenType::STRING || tmp == TokenType::VAR || tmp == TokenType::BOOL || tmp == TokenType::FALSE || tmp == TokenType::TRUE || tmp == TokenType::INPUT || tmp == TokenType::INT)
				{
					found_right = true;
				}
				else if (lexer->tokens[j]->type == TokenType::IF)
				{

					found_right = true;
					If = true;
				}
				end_iter = j + 1;
			}


			if (!found_right)
				throw "Right operand of \"=\" must be variable or number or string";
			if (If)
				root->right = parseIF(i + 2, end_iter);
			else
				root->right = parseExpr(i + 1, end_iter);
			i = end_iter;

			line_nodes.push_back(root);
		}
		else if (type == TokenType::VAR && lexer->tokens[i + 1]->type == TokenType::LEFT_BRACKET)
		{
			if (true)
			{
				size_t name = i;

				++i;

				size_t j = ++i;
				while(lexer->tokens[i]->type != TokenType::COLON && lexer->tokens[i]->type != TokenType::END)
				{
					++i;
				}
				if (lexer->tokens[i]->type == TokenType::COLON)
				{
					//root = std::make_shared<NodeAST>(std::make_shared<Token>(TokenType::FUNC_INIT, lexer->tokens[name]->value));
					root = parseFuncInit(j, i - 1);
					root->token->value = lexer->tokens[name]->value;
					root->token->type = TokenType::FUNC_INIT;
					line_nodes.push_back(root);
					tabs_stack.push(TokenType::FUNC_INIT);
					++i;
				}
				else
				{
					j -= 2;
					--i;
					root = parseExpr(j, i);
					line_nodes.push_back(root);
				}
			}
		}
		else if (type == TokenType::IF)
		{
			root = std::make_shared<NodeAST>(lexer->tokens[i]);
			size_t j = i + 1;
			for (;lexer->tokens[j]->type != TokenType::COLON; ++j);
			root->right = parseExpr(i + 1, j);
			line_nodes.push_back(root);
			tabs_stack.push(TokenType::IF);
			i = j+1;
		}
		else if (type == TokenType::FOR)
		{
			root = std::make_shared<NodeAST>(lexer->tokens[i]);
			size_t j = i + 1;
			for (; lexer->tokens[j]->type != TokenType::COLON; ++j);
			root = parseFor(i + 1, j);
			line_nodes.push_back(root);
			tabs_stack.push(TokenType::FOR);
			i = j + 1;
			++tokens_size;
		}
		else if (type == TokenType::RETURN)
		{
			root = std::make_shared<NodeAST>(lexer->tokens[i]);
			
			bool found_right = false;

			for (size_t j = i + 1; TokenTypeSwitch(lexer->tokens[j]->type) != "END"; ++j)
			{
				std::string tmp = TokenTypeSwitch(lexer->tokens[j]->type);

				if (tmp == "NUMBER" || tmp == "STRING" || tmp == "VAR" || tmp == "BOOL" || tmp == "FALSE" || tmp == "TRUE")
				{
					found_right = true;
				}
				end_iter = j + 1;
			}
			if(found_right)
				root->right = parseExpr(i + 1, end_iter);
			else
			{
				std::cout << "After return must be expression" << "\n";
				system("pause");
			}
			i = end_iter;

			line_nodes.push_back(root);
		}
		else if (type == TokenType::PRINT)
		{
			//����������� ������ print'� � ����� parsePrint();
			if (lexer->tokens[i + 1]->type != TokenType::LEFT_BRACKET)
				//throw "Doesn't ( after print";
			{
				std::cout << "After print must be brackets" << "\n";
				system("pause");
			}
			size_t j = i+2;

			bool found_right = false;
			bool found = false;

			int rbrackets_counter = 0;

			while (lexer->tokens[j]->type != TokenType::END)
			{
				TokenType tmp = lexer->tokens[j]->type;
				if (tmp == TokenType::VAR || tmp == TokenType::NUMBER || tmp == TokenType::STRING || tmp == TokenType::BOOL || tmp == TokenType::TRUE || tmp == TokenType::FALSE)
					found = true;
				else if (lexer->tokens[j]->type == TokenType::LEFT_BRACKET)
					++rbrackets_counter;
				else if (lexer->tokens[j]->type == TokenType::RIGHT_BRACKET && rbrackets_counter == 0)
					found_right = true;
				else if (lexer->tokens[j]->type == TokenType::RIGHT_BRACKET && rbrackets_counter != 0)
					--rbrackets_counter;
				++j;
			}

			//std::cout << "After print must be closed brackets" << "\n";
			//system("pause");

			j-=1;

			if (!found_right)
				//throw "Doesn't ( after print";
			{
				std::cout << "After print must be brackets" << "\n";
				system("pause");
			}

			root = std::make_shared<NodeAST>(lexer->tokens[i]);

			root->right = parseExpr(i + 2, j);

			line_nodes.push_back(root);
			i = j + 1;
		}
	}

	if (line_nodes.back()->token->type != TokenType::END)
		line_nodes.push_back(std::make_shared<NodeAST>(std::make_shared<Token>(TokenType::END, "")));

}