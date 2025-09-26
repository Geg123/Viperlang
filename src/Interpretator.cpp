#include"../include/Creator.h"
#include<fstream>


Interpretator::Interpretator(std::string path)
{
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

	ast = std::make_shared<AST>(&main);
	ast->Analys();

	var_crt.arr_creator = std::make_shared<ArrayCreator>(arr_crt);

	var_crt.arr_creator->var_crt = std::make_shared<VarCreator>(var_crt);

	var_crt.func_creator = std::make_shared<FuncCreator>(func_crt);

	var_crt.func_creator->var_crt = std::make_shared<VarCreator>(var_crt);

	var_crt.my_interpretator = this;

	runtime();

	system("pause");
}


void Interpretator::runtime()
{

	size_t size = ast->line_nodes.size();

	for(size_t i = 0; i < size; ++i)
	{
		std::string node_type = TokenTypeSwitch(ast->line_nodes[i]->token->type);

		if (node_type == "EQ")
		{
			if (TokenTypeSwitch(ast->line_nodes[i]->right->token->type) == "ARR_LIST")
				var_crt.arr_creator->CreateArray(ast->line_nodes[i]);
			else if (TokenTypeSwitch(ast->line_nodes[i]->left->token->type) == "ARRAY")
				var_crt.arr_creator->setArrIndex(ast->line_nodes[i]);
			else
				var_crt.CreateVariables(ast->line_nodes[i]);
			//var_crt.my_interpretator = std::make_shared<Interpretator>(*this);
		}
		else if (node_type == "IF")
		{
			if (var_crt.parseASTNode(ast->line_nodes[i]->right)->token->value == "false")
			{
				while (ast->line_nodes[i]->token->type != StringToTokenType("IF_END"))
				{
					++i;
				}
			}
		}
		else if (node_type == "FOR")
		{
			std::string iterator = ast->line_nodes[i]->left->token->value;

			std::shared_ptr<Variable> tmp = std::make_shared<Variable>(iterator);
			tmp->type = StringToVarType("INT");
			tmp->value = "0";

			var_crt.var_list.insert({ iterator, tmp });

			size_t start = i + 1;
			size_t end = start;

			while (ast->line_nodes[i]->token->type != StringToTokenType("FOR_END"))
			{
				++end;
				++i;
			}

			while (std::stoi(var_crt.var_list[iterator]->value) < std::stoi(var_crt.parseASTNode(ast->line_nodes[start - 1]->right)->token->value))
			{
				runtime(start, end - 1);
				var_crt.var_list[iterator]->value = std::to_string(std::stoi(var_crt.var_list[iterator]->value) + 1);
			}
			i = end - 1;
		}
		else if (node_type == "FUNC_INIT")
		{
			func_crt.CreateFunc(ast->line_nodes[i]);
			std::string func_name = ast->line_nodes[i]->token->value;
			func_crt.functions_list[func_name]->line_nodes_index = ++i;
			while (TokenTypeSwitch(ast->line_nodes[i]->token->type) != "FUNC_END")
				++i;
			func_crt.functions_list[func_name]->last_line_nodes_index = i;
			//var_crt.my_interpretator = std::make_shared<Interpretator>(*this);
		}
		else if (node_type == "FUNCTION")
		{
			if (func_crt.functions_list.count(ast->line_nodes[i]->token->value))
			{
				std::shared_ptr<NodeAST> iter = ast->line_nodes[i];

				size_t var_iter = 0;

				while (iter->right != nullptr)
				{
					iter = iter->right;

					func_crt.functions_list[ast->line_nodes[i]->token->value]->func_var_crt->var_list[func_crt.functions_list[ast->line_nodes[i]->token->value]->vars_names[var_iter]]->value = var_crt.parseASTNode(iter)->token->value;
					func_crt.functions_list[ast->line_nodes[i]->token->value]->func_var_crt->var_list[func_crt.functions_list[ast->line_nodes[i]->token->value]->vars_names[var_iter]]->type = var_crt.TypeInit(iter);

					++var_iter;
				}

				runtime_func(func_crt.functions_list[ast->line_nodes[i]->token->value]->line_nodes_index, func_crt.functions_list[ast->line_nodes[i]->token->value]->last_line_nodes_index, func_crt.functions_list[ast->line_nodes[i]->token->value], true);
			}
		}
		else if (node_type == "PRINT")
		{
			print(ast->line_nodes[i]);
		}
	}
}

void Interpretator::runtime(size_t iter, size_t end_iter)
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

}