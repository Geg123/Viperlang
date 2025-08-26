#include"AST.h"

NodeAST::NodeAST(Token* _token) : token(_token) {}

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

	size_t tokens_size = lexer->tokens.size();

	//заполнение нодами и обработка скобок путём рекурсии

	for (size_t i = iter; i < tokens_size; ++i)
	{
		if (TokenTypeSwitch(lexer->tokens[i]->type) == "MULT")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			mult = true;
		}
		else if (TokenTypeSwitch(lexer->tokens[i]->type) == "DIV")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			mult = true;
		}
		else if (TokenTypeSwitch(lexer->tokens[i]->type) == "VAR")
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
		else if (TokenTypeSwitch(lexer->tokens[i]->type) == "NUM")
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
		else if (TokenTypeSwitch(lexer->tokens[i]->type) == "PLUS")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			plus = true;
		}
		else if (TokenTypeSwitch(lexer->tokens[i]->type) == "MINUS")
		{
			nodes.push_back(std::make_shared<NodeAST>(lexer->tokens[i]));
			plus = true;
		}
		else if (TokenTypeSwitch(lexer->tokens[i]->type) == "LEFT_BRACKET")
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
			nodes.push_back(parseMathExpr(i, j));
		}
		
	}
	/*else if (TokenTypeSwitch(lexer->tokens[i]->type) == "MULT" || TokenTypeSwitch(lexer->tokens[i]->type) == "DIV")
		mult = true;
	else if (TokenTypeSwitch(lexer->tokens[i]->type) == "PLUS" || TokenTypeSwitch(lexer->tokens[i]->type) == "MINUS")
		plus = true; */

	if (mult)
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
			}
			else if (TokenTypeSwitch(nodes[i]->token->type) == "DIV")
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
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
			}
			else if (TokenTypeSwitch(nodes[i]->token->type) == "MINUS")
			{
				nodes[i]->right = nodes[i + 1];
				nodes[i]->left = nodes[i - 1];
				nodes.erase(nodes.begin() + i + 1);
				nodes.erase(nodes.begin() + i - 1);
			}
			--i;
		}
	}

	return nodes[0];
}

std::shared_ptr<NodeAST> AST::parseStringExpr(size_t iter, size_t end_iter)
{
	return nullptr;
}

std::shared_ptr<NodeAST> AST::parseVarExpr(size_t iter, size_t end_iter)
{
	return nullptr;
}

std::shared_ptr<NodeAST> AST::parseIF(size_t iter, size_t end_iter)
{
	return nullptr;
}

std::shared_ptr<NodeAST> AST::parsePrint(size_t iter, size_t end_iter)
{
	return nullptr;
}

void AST::Analys()
{
	std::shared_ptr<NodeAST> root;
	size_t tokens_size = lexer->tokens.size();

	size_t end_iter;

	bool found_right = false;
	bool Var = false;
	bool Num = false;
	bool Str = false;

	for (size_t i = 0; i < tokens_size; ++i)
	{
		if (TokenTypeSwitch(lexer->tokens[i]->type) == "EQ")
		{
			root = std::make_shared<NodeAST>(lexer->tokens[i]);
			if (TokenTypeSwitch(lexer->tokens[i - 1]->type) == "VAR")
				root->left = std::make_shared<NodeAST>(lexer->tokens[i - 1]);
			else
				throw "Left operand of \"=\" must be variable";
			for (size_t j = i + 1; TokenTypeSwitch(lexer->tokens[j]->type) != "END"; ++j)
			{
				if (TokenTypeSwitch(lexer->tokens[j]->type) == "NUM")
				{

					found_right = true;
					Num = true;
					break;
				}
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "STRING")
				{

					found_right = true;
					Str = true;
					break;
				}
				else if (TokenTypeSwitch(lexer->tokens[j]->type) == "VAR")
				{

					found_right = true;
					Var = true;
					break;
				}
				end_iter = j + 1;
			}

			if (!found_right)
				throw "Right operand of \"=\" must be variable or number or string";
			if (Num && Str)
				throw "Error number and string together";
			else if (Var && Num)
				root->right = parseMathExpr(i + 1, end_iter);
			else if (Var && Str)
				root->right = parseStringExpr(i + 1, end_iter);
			else
				root->right = parseVarExpr(i + 1, end_iter);
			i = end_iter;
		}

		else if (TokenTypeSwitch(lexer->tokens[i]->type) == "END")
			continue;
		else if (TokenTypeSwitch(lexer->tokens[i]->type) == "PRINT")
			//определение границ print'а и вызов parsePrint();
			continue;
	}


}