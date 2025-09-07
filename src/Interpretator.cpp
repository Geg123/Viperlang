#include"../include/Interpretator.h"

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

	var_crt.arr_creator->var_creator = std::make_shared<VarCreator>(var_crt);

	var_crt.func_crator = std::make_shared<FuncCreator>(func_crt);

	var_crt.func_crator->var_crt = std::make_shared<VarCreator>(var_crt);

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
		}
		else if (node_type == "PRINT")
		{
			print(ast->line_nodes[i]);
		}
	}
}

void Interpretator::print(std::shared_ptr<NodeAST> node)
{
	if (TokenTypeSwitch(node->right->token->type) == "VAR")
	{
		std::string var_name = node->right->token->value;
		size_t size = var_crt.var_list.size();
			if (var_crt.var_list.count(var_name))
			{
				std::cout << var_crt.var_list[var_name]->value << "\n";
				return;
			}
		std::cout << "Error: var \"" << var_name << "\" doesn't exist\n";
		system("pause");
	}
	else
		std::cout << node->right->token->value << "\n";
}