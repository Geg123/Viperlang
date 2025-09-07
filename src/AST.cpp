#include"../include/AST.h"

NodeAST::NodeAST(std::shared_ptr<Token> _token) : token(_token) {}

AST::AST(Lexer* _lexer): lexer(_lexer){}

//NodeAST* AST::parseEQ(size_t iter)
//{
	//NodeAST* root = new NodeAST(lexer->tokens[iter]);
	//if (TokenTypeSwitch(lexer->tokens[iter - 1]->type) != "VAR")
	//	throw "left operand of = (EQ) must be VAR";
	//root->left = new NodeAST(lexer->tokens[iter - 1]);
	//root->right = parseMathExpr(iter);
//}



//void AST::parseMultAndDiv(size_t& iter)
//{
	//for (;TokenTypeSwitch(lexer->tokens[iter]->type) == "END"; ++iter)
	//{

	//}
//}

std::shared_ptr<NodeAST> AST::parseMathExpr(size_t iter, size_t end_iter)
{	
	std::vector<std::shared_ptr<NodeAST>> nodes;

	bool mult = false;
	bool plus = false;

	//size_t tokens_size = lexer->tokens.size();

	//заполнение нодами и обработка скобок путём рекурсии

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
		else if (type == "VAR" && TokenTypeSwitch(lexer->tokens[i + 1]->type) == "RIGHT_BRACKET")
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
		else if (type == "NUMBER")
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
			nodes.push_back(parseMathExpr(i + 1, j));
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
	/*else if (type == "MULT" || type == "DIV")
		mult = true;
	else if (type == "PLUS" || type == "MINUS")
		plus = true; */

	if (mult && plus)
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
			--i;
		}
	}
	else if (mult)
	{
		size_t i = nodes.size() - 1;
		while (nodes.size() > 1)
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
			--i;
		}
	}
	if (plus)
	{
		size_t i = nodes.size() - 1;
		while(nodes.size() > 1)
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

	return nodes[0];
}

std::shared_ptr<NodeAST> AST::parseStringExpr(size_t iter, size_t end_iter)
{
	std::vector<std::shared_ptr<NodeAST>> nodes;

	bool mult = false;
	bool plus = false;

	//size_t tokens_size = lexer->tokens.size();

	//заполнение нодами и обработка скобок путём рекурсии

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
		else if (type == "VAR")
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
		else if (type == "STRING")
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
		else if (type == "NUMBER")
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
			nodes.push_back(parseMathExpr(i + 1, j));
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
	/*else if (type == "MULT" || type == "DIV")
		mult = true;
	else if (type == "PLUS" || type == "MINUS")
		plus = true; */

	if (mult && plus)
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
				std::cout << "Error: you can't divide the string!\n";
				system("pause");
			}
			--i;
		}
	}
	else if (mult)
	{
		size_t i = nodes.size() - 1;
		while (nodes.size() > 1)
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
				std::cout << "Error: you can't divide the string!\n";
				system("pause");
			}
			--i;
		}
	}
	if (plus)
	{
		size_t i = nodes.size() - 1;
		while (nodes.size() > 1)
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
				std::cout << "Error: you can't subtract from the string!\n";
				system("pause");
			}
			--i;
		}
	}

	return nodes[0];
}

std::shared_ptr<NodeAST> AST::parseVarExpr(size_t iter, size_t end_iter)
{
	if (iter == end_iter || iter + 1 == end_iter)
		return std::make_shared<NodeAST>(lexer->tokens[iter]);
	else
		return nullptr;
	std::vector<std::shared_ptr<NodeAST>> nodes;

	bool mult = false;
	bool plus = false;


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
		else if (type == "VAR")
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
			nodes.push_back(parseVarExpr(i, j));
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

	if (mult && plus)
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
			--i;
		}
	}
	else if (mult)
	{
		size_t i = nodes.size() - 1;
		while (nodes.size() > 1)
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
			--i;
		}
	}
	if (plus)
	{
		size_t i = nodes.size() - 1;
		while (nodes.size() > 1)
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

	return nodes[0];
}

std::shared_ptr<NodeAST> AST::parseIF(size_t iter, size_t end_iter)
{
	return nullptr;
}

std::shared_ptr<NodeAST> AST::parseArray(size_t iter, size_t end_iter)
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
		bool Var = false;
		bool Num = false;
		bool Str = false;


		for (size_t j = current ; TokenTypeSwitch(lexer->tokens[j]->type) != "COMMA" && TokenTypeSwitch(lexer->tokens[j]->type) != "SQ_RIGHT_BRACKET"  ; ++j)
		{
			if (TokenTypeSwitch(lexer->tokens[j]->type) == "NUMBER")
			{

				found_right = true;
				Num = true;
			}
			else if (TokenTypeSwitch(lexer->tokens[j]->type) == "STRING")
			{

				found_right = true;
				Str = true;
			}
			else if (TokenTypeSwitch(lexer->tokens[j]->type) == "VAR")
			{

				found_right = true;
				Var = true;
			}
			curr_end = j;
		}

		++curr_end;

		if (!found_right)
		{
			std::cout << "Element of array must be variable or number or string";
			system("pause");
		}
		if (Num && Str)
			nodes->right = parseStringExpr(current, curr_end);
		else if (Var && Num)
			nodes->right = parseMathExpr(current, curr_end);
		else if (Var && Str)
			nodes->right = parseStringExpr(current, curr_end);
		else if (Num)
			nodes->right = parseMathExpr(current, curr_end);
		else if (Str)
			nodes->right = parseStringExpr(current, curr_end);

		current = ++curr_end;

		if (current != end_iter)
			nodes = nodes->right;
		else
			break;
	}
	return res;
}


std::shared_ptr<NodeAST> AST::parseArrayIndex(size_t right_bracket)
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
		root->right = parseMathExpr(start_iter, end_iter + 1);
		return root;
	}
	else
	{
		std::cout << "Error: array index output must be arr[index]\n";
		system("pause");
	}
}

std::shared_ptr<NodeAST> AST::parseBool(size_t iter, size_t end_iter)
{
	std::vector<std::shared_ptr<NodeAST>> nodes;

	bool and = false;
	bool or = false;
	bool more = false;
	bool if_eq = false;
	bool num = false;
	bool var = false;
	bool False = false;
	bool True = false;

	for (size_t i = iter; i < end_iter; ++i)
	{

		std::string type = TokenTypeSwitch(lexer->tokens[i]->type);
		if (type == "AND")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			and = true;
		}
		else if (type == "TRUE")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			True = true;
		}
		else if (type ==  "NUMBER")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			num = true;
		}
		else if (type == "VAR")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			var = true;
		}
		else if (type == "FALSE")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			False = true;
		}
		else if (type == "OR")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			or = true;
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
			if_eq = true;
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
			nodes.push_back(parseBool(i + 1, j));
			i = j;
		}
	}

	if ((var || False || True) && (end_iter - iter) == 1)
	{
		nodes[0]->token->type = StringToTokenType("BOOL");
		return nodes[0];
	}

	if (more && (or || and))
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
	else if(more){
		size_t i = nodes.size() - 1;
			while (nodes.size() > 1)
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
	if (if_eq && !(or || and || more))
	{
		size_t i = nodes.size() - 1;
		while (nodes.size() > 1)
		{
			if (TokenTypeSwitch(nodes[i]->token->type) == "IS_EQ")
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
	else if (if_eq)
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
			--i;
		}
	}
	if (and && or)
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
	else if (and)
	{
		size_t i = nodes.size() - 1;
		while (nodes.size() > 1)
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
		while (nodes.size() > 1)
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
	if (if_eq && !(or || and || more))
	{
		size_t i = nodes.size() - 1;
		while (nodes.size() > 1)
		{
			if (TokenTypeSwitch(nodes[i]->token->type) == "IS_EQ")
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
	else if (if_eq)
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
			--i;
		}
	}

	return nodes[0];
}

void AST::Analys()
{
	std::shared_ptr<NodeAST> root;
	size_t tokens_size = lexer->tokens.size();

	size_t end_iter;

	

	for (size_t i = 0; i < tokens_size; ++i)
	{
		std::string type = TokenTypeSwitch(lexer->tokens[i]->type);

		if (type == "EQ")
		{
			bool found_right = false;
			bool Var = false;
			bool Num = false;
			bool Str = false;
			bool ArrDef = false;
			bool Arr = false;
			bool Bool = false;

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
				if (TokenTypeSwitch(lexer->tokens[j]->type) == "SQ_LEFT_BRACKET" && TokenTypeSwitch(lexer->tokens[j - 1]->type) == "EQ")
				{
					found_right = true;
					ArrDef = true;
				}
				if (TokenTypeSwitch(lexer->tokens[j]->type) == "SQ_LEFT_BRACKET" && TokenTypeSwitch(lexer->tokens[j - 1]->type) != "EQ")
				{
					found_right = true;
					Arr = true;
				}
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "NUMBER")
				{

					found_right = true;
					Num = true;
				}
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "STRING")
				{

					found_right = true;
					Str = true;
				}
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "IS_EQ")
				{

					found_right = true;
					Bool = true;
				}
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "VAR")
				{

					found_right = true;
					Var = true;
				}
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "TRUE" || TokenTypeSwitch(lexer->tokens[j]->type) == "FALSE")
				{
					found_right = true;
					Bool = true;
				}
				end_iter = j + 1;
			}

			if (!found_right)
				throw "Right operand of \"=\" must be variable or number or string";
			if (ArrDef)
				root->right = parseArray(i + 2, end_iter);
			else if(Bool)
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
			else
				root->right = parseVarExpr(i + 1, end_iter);
			i = end_iter;

			line_nodes.push_back(root);
		}

		else if (type == "END")
			continue;
		else if (type == "PRINT")
		{
			//определение границ print'а и вызов parsePrint();
			if (TokenTypeSwitch(lexer->tokens[i + 1]->type) != "LEFT_BRACKET")
				//throw "Doesn't ( after print";
			{
				std::cout << "After print must be brackets" << "\n";
				system("pause");
			}
			size_t j = i+2;

			bool found_right = false;
			bool Var = false;
			bool Num = false;
			bool Str = false;

			int rbrackets_counter = 0;

			while (TokenTypeSwitch(lexer->tokens[j]->type) != "END")
			{
				if (TokenTypeSwitch(lexer->tokens[j]->type) == "VAR")
					Var = true;
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "NUMBER")
					Num = true;
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "STRING")
					Str = true;
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

			else if (Num && Str)
			{
				std::cout << "Number and str together" << "\n";
				system("pause");
			}

			root = std::make_shared<NodeAST>(lexer->tokens[i]);

			if (Var && Num)
				root->right = parseMathExpr(i + 2, j);
			else if (Var && Str)
				root->right = parseStringExpr(i + 2, j);
			else if (Num)
				root->right = parseMathExpr(i + 2, j);
			else if (Var)
				root->right = parseVarExpr(i + 2, j);
			else if (Str)
				root->right = parseStringExpr(i + 2, j);
			else
			{
				std::cout << "Nothing to parse";
				system("pause");
			}

			line_nodes.push_back(root);
			i = j + 1;
		}
	}


}