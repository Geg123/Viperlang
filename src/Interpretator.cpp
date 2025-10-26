#include"../include/Interpretator.h"
#include<fstream>


Interpretator::Interpretator(std::string path)
{
	Parser::line_nodes;
	std::ifstream file;
	file.open(path);
	if (file.is_open()) {
		std::string in;
		
		while (std::getline(file, in))
		{
			main.line = in;
			main.Analys();
		}
		//main.printTokens();
	}
	else
		std::cout << "File not opened!";

	file.close();
	parser.ParserLexerInit(&main);
	parser.Analys();
	ObjectManager::start();
	runtime();
	system("pause");
}

void ObjectManager::CalcExpr(std::shared_ptr<NodeAST> node)
{
	OperatorsManager::DoOperation(node);
}

void ToBool(std::shared_ptr<NodeAST> node)
{
	TokenType type = node->token->type;
	std::string value = node->token->value;
	if(type == TokenType::NUMBER && value == "0")
	{
		node->token->type = TokenType::BOOL;
		node->token->value = "False";
	}
	else if(type == TokenType::STRING && (value == "0" || value == ""))
	{
		node->token->type = TokenType::BOOL;
		node->token->value = "False";
	}
	else if((type == TokenType::FALSE || type == TokenType::BOOL) && value == "False")
	{
		node->token->type = TokenType::BOOL;
		node->token->value = "False";
	}
	else
	{
		node->token->type = TokenType::BOOL;
		node->token->value = "True";
	}
}

void Interpretator::runtime()
{
	VarCreator var_crt;
	FuncCreator func_crt;
	ArrayCreator arr_crt;
	size_t size = parser.line_nodes.size();
	for(size_t i = 0; i < size; ++i)
	{
		std::shared_ptr<NodeAST> node = parser.line_nodes[i];
		TokenType type = node->token->type;
		if(type == TokenType::EQ)
		{
			var_crt.CreateObject(node);
		}
		else if(type == TokenType::FUNCTION)
		{
			ObjectManager::getValue(node);
		}
		else if(type == TokenType::ARR_LIST)
		{
			arr_crt.CreateObject(node);
		}
		else if(type == TokenType::IF)
		{
			ObjectManager::CalcExpr(node->right);
			ToBool(node->right);
			if(node->right->token->value == "False")
			{
				++i;
				size_t counter = 0;
				while(true)
				{
					TokenType type = parser.line_nodes[i]->token->type;
					if(type == TokenType::IF)
						++counter;
					else if(type == TokenType::IF_END && counter != 0)
						--counter;
					else if(type == TokenType::IF_END && counter == 0 || type == TokenType::FUNC_END || type == TokenType::END)
						break;
					++i;
				}
			}
		}
		else if(type == TokenType::FUNC_INIT)
		{
			func_crt.CreateObject(node, i);
		}
		else if(type == TokenType::PRINT)
		{
			ObjectManager::CalcExpr(node->right);
			std::cout << node->right->token->value << "\n";
		}
	}
	system("pause");
}

/*void Interpretator::runtime(size_t iter, size_t end_iter)
{

	for (; iter < end_iter; ++iter)
	{
		std::string node_type = TokenTypeSwitch(ast->line_nodes[iter]->token->type);

		if (node_type == "EQ")
		{
			if (TokenTypeSwitch(ast->line_nodes[iter]->right->token->type) == "ARR_LIST")
				var_crt.arr_creator->CreateArray(ast->line_nodes[iter]);
			else if (TokenTypeSwitch(ast->line_nodes[iter]->left->token->type) == "ARRAY")
				var_crt.arr_creator->setArrIndex(ast->line_nodes[iter]);
			else
				var_crt.CreateVariables(ast->line_nodes[iter]);
		}
		else if (node_type == "IF")
		{
			if (var_crt.parseASTNode(ast->line_nodes[iter]->right)->token->value == "false")
			{
				while (ast->line_nodes[iter]->token->type != StringToTokenType("IF_END"))
				{
					++iter;
				}
			}
		}
		else if (node_type == "FUNCTION")
		{
			
		}
		else if (node_type == "PRINT")
		{
			std::shared_ptr<NodeAST> node = std::make_shared<NodeAST>(std::make_shared<Token>(StringToTokenType("PRINT"), ""));
			node->right	= var_crt.parseASTNode(ast->line_nodes[iter]->right);
			print(node);
		}
	}
}

std::shared_ptr<NodeAST> Interpretator::runtime_func(size_t iter, size_t end_iter, std::shared_ptr<Function> function, bool f)
{
	for (; iter < end_iter; ++iter)
	{
		std::string node_type = TokenTypeSwitch(ast->line_nodes[iter]->token->type);

		if (node_type == "EQ")
		{
			if (TokenTypeSwitch(ast->line_nodes[iter]->right->token->type) == "ARR_LIST")
				function->func_var_crt->arr_creator->CreateArray(ast->line_nodes[iter]);
			else if (TokenTypeSwitch(ast->line_nodes[iter]->left->token->type) == "ARRAY")
				function->func_var_crt->arr_creator->setArrIndex(ast->line_nodes[iter]);
			else
				function->func_var_crt->CreateVariables(ast->line_nodes[iter]);
		}
		else if (node_type == "IF")
		{
			if (function->func_var_crt->parseASTNode(ast->line_nodes[iter]->right)->token->value == "false")
			{
				while (ast->line_nodes[iter]->token->type != StringToTokenType("IF_END"))
				{
					++iter;
				}
			}
		}
		else if (node_type == "RETURN")
		{
			return ast->line_nodes[iter]->right;
		}
		else if (node_type == "PRINT")
		{
			std::shared_ptr<NodeAST> node = std::make_shared<NodeAST>(std::make_shared<Token>(StringToTokenType("PRINT"), ""));
			node->right = function->func_var_crt->parseASTNode(ast->line_nodes[iter]->right);
			print(node);
		}
	}
}

void Interpretator::print(std::shared_ptr<NodeAST> node)
{
	node->right = var_crt.parseASTNode(node->right);
	std::cout << node->right->token->value << "\n";
	return;

}*/