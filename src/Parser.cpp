#include"../include/Parser.h"

NodeAST::NodeAST(std::shared_ptr<Token> _token) : token(_token) {}

Parser::Parser(Lexer* _lexer): lexer(_lexer){}

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

	for (size_t i = iter; i < end_iter; ++i)
	{
		std::string type = TokenTypeSwitch(lexer->tokens[i]->type);

		if (type == "MULT")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			mult = true;
		}
		else if (type == "DIV")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			mult = true;
		}
		else if (type == "MODULE")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			mult = true;
		}
		else if (type == "INPUT")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			int brackets_pares = 0;
			size_t j = i + 2;
			if (TokenTypeSwitch(lexer->tokens[i + 1]->type) == "LEFT_BRACKET") {
				while (1)
				{
					if (TokenTypeSwitch(lexer->tokens[j]->type) == "LEFT_BRACKET")
						++brackets_pares;
					else if (TokenTypeSwitch(lexer->tokens[j]->type) == "RIGHT_BRACKET" && brackets_pares != 0)
						--brackets_pares;
					else if (TokenTypeSwitch(lexer->tokens[j]->type) == "RIGHT_BRACKET" && brackets_pares == 0)
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
		else if (type == "INT")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			int brackets_pares = 0;
			size_t j = i + 2;
			if (TokenTypeSwitch(lexer->tokens[i + 1]->type) == "LEFT_BRACKET") {
				while (1)
				{
					if (TokenTypeSwitch(lexer->tokens[j]->type) == "LEFT_BRACKET")
						++brackets_pares;
					else if (TokenTypeSwitch(lexer->tokens[j]->type) == "RIGHT_BRACKET" && brackets_pares != 0)
						--brackets_pares;
					else if (TokenTypeSwitch(lexer->tokens[j]->type) == "RIGHT_BRACKET" && brackets_pares == 0)
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
		else if (type == "VAR")
		{
			if (TokenTypeSwitch(lexer->tokens[i + 1]->type) == "LEFT_BRACKET")
			{
				lexer->tokens[i]->type = StringToTokenType("FUNCTION");
				nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));

				size_t current = i;
				size_t curr_end = current;

				std::shared_ptr<NodeAST> tmp = nodes[nodes.size() - 1];

				while (1)
				{
					bool found_right = false;

					for (size_t j = current; TokenTypeSwitch(lexer->tokens[j]->type) != "COMMA" && TokenTypeSwitch(lexer->tokens[j]->type) != "RIGHT_BRACKET"; ++j)
					{
						if (TokenTypeSwitch(lexer->tokens[j]->type) == "NUMBER")
						{
							found_right = true;
						}
						else if (TokenTypeSwitch(lexer->tokens[j]->type) == "STRING")
						{
							found_right = true;
						}
						else if (TokenTypeSwitch(lexer->tokens[j]->type) == "BOOL")
						{
							found_right = true;
						}
						else if (TokenTypeSwitch(lexer->tokens[j]->type) == "VAR")
						{
							found_right = true;
						}
						curr_end = j;
					}

					++curr_end;

					if (found_right)
					{
						tmp->right = parseExpr(current, curr_end);
					}

					current = ++curr_end;

					if (TokenTypeSwitch(lexer->tokens[current - 1]->type) != "RIGHT_BRACKET")
						tmp = tmp->right;
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
		else if (type == "NUMBER")
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
		else if (type == "STRING")
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
		else if (type == "TRUE")
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
		else if (type == "FALSE")
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
		else if (type == "PLUS")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			plus = true;
		}
		else if (type == "MINUS")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			plus = true;
		}
		else if (type == "GREATER")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			more = true;
		}
		else if (type == "LESS")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			more = true;
		}
		else if (type == "IS_EQ")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			is_eq = true;
		}
		else if (type == "NOT_EQ")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			is_eq = true;
		}
		else if (type == "AND")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			and = true;
		}
		else if (type == "OR")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			or = true;
		}
		else if (type == "LEFT_BRACKET")
		{
			int brackets_pares = 0;
			size_t j = i + 1;
			while (1)
			{
				if (TokenTypeSwitch(lexer->tokens[j]->type) == "LEFT_BRACKET")
					++brackets_pares;
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "RIGHT_BRACKET" && brackets_pares != 0)
					--brackets_pares;
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "RIGHT_BRACKET" && brackets_pares == 0)
					break;
				++j;
			}
			nodes.push_back(parseExpr(i + 1, j));
			i = j;
		}
		else if (type == "SQ_LEFT_BRACKET")
		{
			int brackets_pares = 0;
			size_t j = i + 1;
			while (1)
			{
				if (TokenTypeSwitch(lexer->tokens[j]->type) == "SQ_LEFT_BRACKET")
					++brackets_pares;
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "SQ_RIGHT_BRACKET" && brackets_pares != 0)
					--brackets_pares;
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "SQ_RIGHT_BRACKET" && brackets_pares == 0)
					break;
				++j;
			}
			nodes.push_back(parseArrayIndex(j));
			i = j;
		}

	}

	if (mult)
	{
		size_t i = nodes.size() - 1;
		while (i >= 1 && i != 18446744073709551615)
		{
			if (TokenTypeSwitch(nodes[i]->token->type) == "MULT")
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			else if (TokenTypeSwitch(nodes[i]->token->type) == "DIV")
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			else if (TokenTypeSwitch(nodes[i]->token->type) == "MODULE")
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
			if (TokenTypeSwitch(nodes[i]->token->type) == "PLUS")
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			else if (TokenTypeSwitch(nodes[i]->token->type) == "MINUS")
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
			if (TokenTypeSwitch(nodes[i]->token->type) == "GREATER")
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			else if (TokenTypeSwitch(nodes[i]->token->type) == "LESS")
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
			if (TokenTypeSwitch(nodes[i]->token->type) == "IS_EQ")
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
				--i;
			}
			else if (TokenTypeSwitch(nodes[i]->token->type) == "NOT_EQ")
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
			if (TokenTypeSwitch(nodes[i]->token->type) == "AND")
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
			if (TokenTypeSwitch(nodes[i]->token->type) == "OR")
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
	std::shared_ptr<NodeAST> nodes = std::make_shared<NodeAST>(std::make_shared<Token>(StringToTokenType("ARR_LIST"),""));
	size_t node_iter = 0;

	size_t current = iter;
	size_t curr_end;
	nodes->token->type = StringToTokenType("ARR_LIST");

	std::shared_ptr<NodeAST> res = nodes;

	while (1)
	{
		bool found_right = false;

		for (size_t j = current ; TokenTypeSwitch(lexer->tokens[j]->type) != "COMMA" && TokenTypeSwitch(lexer->tokens[j]->type) != "SQ_RIGHT_BRACKET"  ; ++j)
		{
			if (TokenTypeSwitch(lexer->tokens[j]->type) == "NUMBER")
			{
				found_right = true;
			}
			else if (TokenTypeSwitch(lexer->tokens[j]->type) == "STRING")
			{
				found_right = true;
			}
			else if (TokenTypeSwitch(lexer->tokens[j]->type) == "VAR")
			{
				found_right = true;
			}
			else if (TokenTypeSwitch(lexer->tokens[j]->type) == "BOOL")
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
		nodes->right = parseExpr(current, curr_end);

		current = ++curr_end;

		if (current != end_iter)
			nodes = nodes->right;
		else
			break;
	}
	return res;
}


std::shared_ptr<NodeAST> Parser::parseArrayIndex(size_t right_bracket)
{
	std::shared_ptr<NodeAST> root;

	size_t end_iter = right_bracket - 1;
	size_t start_iter = end_iter;
	while (TokenTypeSwitch(lexer->tokens[start_iter]->type) != "SQ_LEFT_BRACKET" && TokenTypeSwitch(lexer->tokens[start_iter]->type) != "END")
	{
		--start_iter;
	}

	++start_iter;

	if ((TokenTypeSwitch(lexer->tokens[start_iter]->type) == "VAR" || TokenTypeSwitch(lexer->tokens[start_iter]->type) == "NUMBER")&& TokenTypeSwitch(lexer->tokens[end_iter]->type) != "SQ_LEFT_BRACKET")
	{
		root = std::make_shared<NodeAST>(lexer->tokens[start_iter - 2]);
		root->token->type = StringToTokenType("ARRAY");
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

		for (size_t j = current; TokenTypeSwitch(lexer->tokens[j]->type) != "COMMA" && TokenTypeSwitch(lexer->tokens[j]->type) != "RIGHT_BRACKET"; ++j)
		{
			if (TokenTypeSwitch(lexer->tokens[j]->type) == "NUMBER")
			{
				found_right = true;
			}
			else if (TokenTypeSwitch(lexer->tokens[j]->type) == "STRING")
			{
				found_right = true;
			}
			else if (TokenTypeSwitch(lexer->tokens[j]->type) == "BOOL")
			{
				found_right = true;
			}
			else if (TokenTypeSwitch(lexer->tokens[j]->type) == "VAR")
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

	unsigned char if_tab_q = 0;
	unsigned char func_tab_q = 0;
	unsigned char cycle_tab_q = 0;

	bool last_end = false;
	

	for (size_t i = 0; i < tokens_size; ++i)
	{
		if (lexer->tokens.size() <= i)
		{
			root = std::make_shared<NodeAST>(std::make_shared<Token>(StringToTokenType("FOR_END"), ""));
			//root->token->type = StringToTokenType("IF_END");
			--cycle_tab_q;
			line_nodes.push_back(root);
			return;
		}

		std::string type = TokenTypeSwitch(lexer->tokens[i]->type);
		size_t tabs = 0;
		for (; TokenTypeSwitch(lexer->tokens[i]->type) == "TAB"; ++tabs, ++i){}
		type = TokenTypeSwitch(lexer->tokens[i]->type);

		if (tabs < (if_tab_q + func_tab_q + cycle_tab_q))
		{
			if (tabs < func_tab_q)
			{
				root = std::make_shared<NodeAST>(std::make_shared<Token>(StringToTokenType("FUNC_END"), ""));
				--func_tab_q;
				line_nodes.push_back(root);
			}
			if ((tabs - func_tab_q - cycle_tab_q) < if_tab_q)
			{
				root = std::make_shared<NodeAST>(std::make_shared<Token>(StringToTokenType("IF_END"), ""));
				//root->token->type = StringToTokenType("IF_END");
				--if_tab_q;
				line_nodes.push_back(root);
			}
			if ((tabs - func_tab_q - if_tab_q) < cycle_tab_q)
			{
				root = std::make_shared<NodeAST>(std::make_shared<Token>(StringToTokenType("FOR_END"), ""));
				//root->token->type = StringToTokenType("IF_END");
				--cycle_tab_q;
				--tokens_size;
				line_nodes.push_back(root);
			}
		}

		if (type == "EQ")
		{
			bool found_right = false;
			bool ArrDef = false;
			bool If = false;

			root = std::make_shared<NodeAST>(lexer->tokens[i]);
			if (TokenTypeSwitch(lexer->tokens[i - 1]->type) == "VAR")
				root->left = std::make_shared<NodeAST>(lexer->tokens[i - 1]);
			else if (TokenTypeSwitch(lexer->tokens[i - 1]->type) == "SQ_RIGHT_BRACKET")
			{
				root->left = parseArrayIndex(i - 1);
			}
			else
				throw "Left operand of \"=\" must be variable";
			for (size_t j = i + 1; TokenTypeSwitch(lexer->tokens[j]->type) != "END"; ++j)
			{
				std::string tmp =  TokenTypeSwitch(lexer->tokens[j]->type);
				if (TokenTypeSwitch(lexer->tokens[j]->type) == "SQ_LEFT_BRACKET" && TokenTypeSwitch(lexer->tokens[j - 1]->type) == "EQ")
				{
					found_right = true;
					ArrDef = true;
				}
				else if (tmp == "NUMBER" || tmp == "STRING" || tmp == "VAR" || tmp == "BOOL" || tmp == "FALSE" || tmp == "TRUE" || tmp == "INPUT")
				{
					found_right = true;
				}
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "IF")
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
		else if (type == "END")
		{
			continue;
		}
		else if (type == "VAR" && TokenTypeSwitch(lexer->tokens[i + 1]->type) == "EQ")
		{
			++i;
			bool found_right = false;
			bool ArrDef = false;
			bool If = false;

			root = std::make_shared<NodeAST>(lexer->tokens[i]);
			if (TokenTypeSwitch(lexer->tokens[i - 1]->type) == "VAR")
				root->left = std::make_shared<NodeAST>(lexer->tokens[i - 1]);
			else if (TokenTypeSwitch(lexer->tokens[i - 1]->type) == "SQ_RIGHT_BRACKET")
			{
				root->left = parseArrayIndex(i - 1);
			}
			else
				throw "Left operand of \"=\" must be variable";
			for (size_t j = i + 1; TokenTypeSwitch(lexer->tokens[j]->type) != "END"; ++j)
			{
				std::string tmp = TokenTypeSwitch(lexer->tokens[j]->type);
				if (TokenTypeSwitch(lexer->tokens[j]->type) == "SQ_LEFT_BRACKET" && TokenTypeSwitch(lexer->tokens[j - 1]->type) == "EQ")
				{
					found_right = true;
					ArrDef = true;
				}
				else if (tmp == "NUMBER" || tmp == "STRING" || tmp == "VAR" || tmp == "BOOL" || tmp == "FALSE" || tmp == "TRUE" || tmp == "INPUT" || tmp == "INT")
				{
					found_right = true;
				}
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "IF")
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
			else
				root->right = parseExpr(i + 1, end_iter);
			i = end_iter;

			line_nodes.push_back(root);
		}
		else if (type == "LEFT_BRACKET")
		{
			if (TokenTypeSwitch(lexer->tokens[i - 1]->type) == "VAR")
			{
				size_t name = i - 1;

				size_t j = ++i;
				while(TokenTypeSwitch(lexer->tokens[i]->type) != "COLON" && TokenTypeSwitch(lexer->tokens[i]->type) != "END")
				{
					++i;
				}
				if (TokenTypeSwitch(lexer->tokens[i]->type) == "COLON")
				{
					root = std::make_shared<NodeAST>(std::make_shared<Token>(StringToTokenType("FUNC_INIT"), lexer->tokens[name]->value));
					root = parseFuncInit(j, i - 1);
					root->token->type = StringToTokenType("FUNC_INIT");
					line_nodes.push_back(root);
					++func_tab_q;
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
		else if (type == "IF")
		{
			root = std::make_shared<NodeAST>(lexer->tokens[i]);
			size_t j = i + 1;
			for (; TokenTypeSwitch(lexer->tokens[j]->type) != "COLON"; ++j);
			root->right = parseExpr(i + 1, j);
			line_nodes.push_back(root);
			++if_tab_q;
			i = j+1;
		}
		else if (type == "FOR")
		{
			root = std::make_shared<NodeAST>(lexer->tokens[i]);
			size_t j = i + 1;
			for (; TokenTypeSwitch(lexer->tokens[j]->type) != "COLON"; ++j);
			root = parseFor(i + 1, j);
			line_nodes.push_back(root);
			++cycle_tab_q;
			i = j + 1;
			++tokens_size;
		}
		else if (type == "RETURN")
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
		else if (type == "PRINT")
		{
			//����������� ������ print'� � ����� parsePrint();
			if (TokenTypeSwitch(lexer->tokens[i + 1]->type) != "LEFT_BRACKET")
				//throw "Doesn't ( after print";
			{
				std::cout << "After print must be brackets" << "\n";
				system("pause");
			}
			size_t j = i+2;

			bool found_right = false;
			bool found = false;

			int rbrackets_counter = 0;

			while (TokenTypeSwitch(lexer->tokens[j]->type) != "END")
			{
				std::string tmp = TokenTypeSwitch(lexer->tokens[j]->type);
				if (tmp == "VAR" || tmp == "NUMBER" || tmp == "STRING" || tmp == "BOOL" || tmp == "TRUE" || tmp == "FALSE")
					found = true;
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "LEFT_BRACKET")
					++rbrackets_counter;
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "RIGHT_BRACKET" && rbrackets_counter == 0)
					found_right = true;
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "RIGHT_BRACKET" && rbrackets_counter != 0)
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


}