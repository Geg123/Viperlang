#include"../include/Var.h"

Function::Function(std::string _name): name(_name)
{
	func_var_crt = std::make_shared<VarCreator>();

	func_var_crt->arr_creator = std::make_shared<ArrayCreator>();

	func_var_crt->arr_creator->var_crt = func_var_crt;
}

void FuncCreator::CreateFunc(std::shared_ptr<NodeAST> node_func)
{
	if (functions_list.count(node_func->token->value))
	{
		functions_list.erase(node_func->token->value);
	}

	std::shared_ptr<NodeAST> node_start = node_func;
	std::shared_ptr<NodeAST> tmp_node;
	std::string func_name = node_func->token->value;
	std::shared_ptr<Function> root = std::make_shared<Function>(func_name);

	while (node_func->right != nullptr)
	{
		node_func = node_func->right;
		Variable tmp(node_func->token->value);
		root->func_var_crt->var_list[node_func->token->value] = std::make_shared<Variable>(tmp);
		root->vars_names.push_back(node_func->token->value);
	}

	functions_list[root->name] = root;
}


