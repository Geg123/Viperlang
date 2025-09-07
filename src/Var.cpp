#include"../include/Var.h"

enum class VarType {INT, STRING, BOOL, FLOAT};

VarType StringToVarType(std::string str)
{
	if (str == "INT")
		return VarType::INT;
	else if (str == "STRING")
		return VarType::STRING;
	else if (str == "BOOL")
		return VarType::BOOL;
	else if (str == "FLOAT")
		return VarType::FLOAT;
}


Variable::Variable(std::string _name): name(_name) {}

void VarCreator::CreateVariables(std::shared_ptr<NodeAST> node_eq)
{
	std::shared_ptr<NodeAST> iter;
	std::string tmp = node_eq->left->token->value;

	size_t size = var_list.size();
		if (var_list.count(tmp))
		{
			iter = node_eq->right;
			iter = parseASTNode(iter);

			var_list[node_eq->left->token->value]->value = iter->token->value;
			var_list[node_eq->left->token->value]->type = TypeInit(iter);
			return;
		}
		else if (arr_creator->list_of_arrays.count(tmp))
		{
			arr_creator->list_of_arrays.erase(tmp);
		}
	

	var_list[tmp] = std::make_shared<Variable>(tmp);

	iter = node_eq->right;
	iter = parseASTNode(iter);

	var_list[tmp]->value = iter->token->value;

	var_list[tmp]->type = TypeInit(iter);
}

std::shared_ptr<NodeAST> VarCreator::parseASTNode(std::shared_ptr<NodeAST> node)
{
	std::string token_type = TokenTypeSwitch(node->token->type);
	if (token_type == "NUMBER")
	{
		return node;
	}
	else if (token_type == "STRING")
	{
		return node;
	}
	else if (token_type == "BOOL")
	{
		return node;
	}
	else if (token_type == "VAR")
	{
		std::string var_name = node->token->value;
		size_t size = list_iter + 1;
			if (var_list.count(var_name))
			{
				if (var_list[var_name]->type == VarType::INT)
				{
					node->token->type = StringToTokenType("NUMBER");
					node->token->value = var_list[var_name]->value;
					return node;
				}
				else if (var_list[var_name]->type == VarType::STRING)
				{
					node->token->type = StringToTokenType("STRING");
					node->token->value = var_list[var_name]->value;
					return node;
				}
				else if (var_list[var_name]->type == VarType::BOOL)
				{
					node->token->type = StringToTokenType("BOOL");
					node->token->value = var_list[var_name]->value;
					return node;
				}
			}
		std::cout << "Error: var "<< var_name << "doesn't exist\n";
		system("pause");
	}
	else if(token_type == "ARRAY")
	{
		std::string arr_name = node->token->value;
		size_t size = arr_creator->list_of_arrays.size();
			if (arr_creator->list_of_arrays.count(arr_name))
			{
				int j = std::stoi(node->right->token->value);
				if (j < arr_creator->list_of_arrays[arr_name]->array.size())
				{
					node->token->value = arr_creator->list_of_arrays[arr_name]->array[j].value;
					VarType type = arr_creator->list_of_arrays[arr_name]->array[j].type;
					if (type == VarType::INT)
					{
						node->token->type = StringToTokenType("NUMBER");
						return node;
					}
					else if (type == VarType::STRING)
					{
						node->token->type = StringToTokenType("STRING");
						return node;
					}
					else if (type == VarType::BOOL)
					{
						node->token->type = StringToTokenType("BOOL");
						return node;
					}
				}
				else
				{
					std::cout << "Error: index " << j << " out of range " << arr_name << " array!\n";
					system("pause");
				}
					
			}
	}
	else if (token_type == "PLUS")
	{
		std::string left = TokenTypeSwitch(node->left->token->type);
		std::string right = TokenTypeSwitch(node->right->token->type);

		if (left == "STRING" && right == "STRING" )
		{
			node->token->type = StringToTokenType("STRING");
			node->token->value = node->left->token->value + node->right->token->value;
			return node;
		}
		else if (left == "NUMBER" && right == "NUMBER")
		{
			node->token->type = StringToTokenType("NUMBER");
			node->token->value = std::to_string(std::stoi(node->left->token->value) + std::stoi(node->right->token->value));
			return node;
		}
		else if(left == "VAR" && right == "STRING")
		{ 
			std::string var_name = node->left->token->value;
			bool found = false;
			size_t size = list_iter + 1;
				if (var_list.count(var_name))
				{
					found = true;
					if (var_list[var_name]->type == VarType::STRING)
					{
						node->token->type = StringToTokenType("STRING");
						node->token->value = var_list[var_name]->value + node->right->token->value;
						return node;
					}
				}
		}
		else if (left == "STRING" && right == "VAR")
		{
			std::string var_name = node->right->token->value;
			bool found = false;
			size_t size = list_iter + 1;
				if (var_list.count(var_name))
				{
					found = true;
					if (var_list[var_name]->type == VarType::STRING)
					{
						node->token->type = StringToTokenType("STRING");
						node->token->value = var_list[var_name]->value + node->left->token->value;
						return node;
					}
					else
					{
						std::cout << "Error: sum of string and number!\n";
						system("pause");
					}
				}
		}
		else if (left == "VAR" && right == "NUMBER")
		{
			std::string var_name = node->left->token->value;
			bool found = false;
			size_t size = list_iter + 1;
			if (var_list[var_name]->name == var_name)
			{
				found = true;
				if (var_list[var_name]->type == VarType::INT)
				{
					node->token->type = StringToTokenType("NUMBER");
					node->token->value = std::to_string(std::stoi(var_list[var_name]->value) + std::stoi(node->right->token->value));
					return node;
				}
			}

		}
		else if (left == "NUMBER" && right == "VAR")
		{
			std::string var_name = node->right->token->value;
			bool found = false;
			size_t size = list_iter + 1;
				if (var_list.count(var_name))
				{
					found = true;
					if (var_list[var_name]->type == VarType::INT)
					{
						node->token->type = StringToTokenType("NUMBER");
						node->token->value = std::to_string(std::stoi(var_list[var_name]->value) + std::stoi(node->left->token->value));
						return node;
					}
				}
		}
		else if (left == "NUMBER" && right == "STRING")
		{
			std::cout << "Error: string + number !\n";
			system("pause");
		}
		else
		{
			node->left = parseASTNode(node->left);
			node->right = parseASTNode(node->right);
			parseASTNode(node);
			return node;
		}
		
	}
	else if (token_type == "MINUS")
	{
		std::string left = TokenTypeSwitch(node->left->token->type);
		std::string right = TokenTypeSwitch(node->right->token->type);

		if (left == "NUMBER" && right == "NUMBER")
		{
			node->token->type = StringToTokenType("NUMBER");
			node->token->value = std::to_string(std::stoi(node->left->token->value) - std::stoi(node->right->token->value));
			return node;
		}
		else if (left == "VAR" && right == "NUMBER")
		{
			std::string var_name = node->left->token->value;
			bool found = false;
			size_t size = list_iter + 1;
				if (var_list.count(var_name))
				{
					found = true;
					if (var_list[var_name]->type == VarType::INT)
					{
						node->token->type = StringToTokenType("NUMBER");
						node->token->value = std::to_string(std::stoi(var_list[var_name]->value) - std::stoi(node->right->token->value));
						return node;
					}
				}
		}
		else if (left == "NUMBER" && right == "VAR")
		{
			std::string var_name = node->right->token->value;
			bool found = false;
			size_t size = list_iter + 1;
				if (var_list.count(var_name))
				{
					found = true;
					if (var_list[var_name]->type == VarType::INT)
					{
						node->token->type = StringToTokenType("NUMBER");
						node->token->value = std::to_string(std::stoi(var_list[var_name]->value) - std::stoi(node->left->token->value));
						return node;
					}
				}
		}
		else if (left == "NUMBER" && right == "STRING")
		{
			std::cout << "Error: string - number !\n";
			system("pause");
		}
		else if (left == "STRING" && right == "NUMBER")
		{
			std::cout << "Error: string - number !\n";
			system("pause");
		}
		else
		{
			node->left = parseASTNode(node->left);
			node->right = parseASTNode(node->right);
			parseASTNode(node);
			return node;
		}
	}
	else if (token_type == "MULT")
	{
		std::string left = TokenTypeSwitch(node->left->token->type);
		std::string right = TokenTypeSwitch(node->right->token->type);

		if (left == "NUMBER" && right == "NUMBER")
		{
			node->token->type = StringToTokenType("NUMBER");
			node->token->value = std::to_string(std::stoi(node->left->token->value) * std::stoi(node->right->token->value));
			return node;
		}
		else if (left == "VAR" && right == "NUMBER")
		{
			std::string var_name = node->left->token->value;
			bool found = false;
			size_t size = list_iter + 1;
				if (var_list.count(var_name))
				{
					found = true;
					if (var_list[var_name]->type == VarType::INT)
					{
						node->token->type = StringToTokenType("NUMBER");
						node->token->value = std::to_string(std::stoi(var_list[var_name]->value) * std::stoi(node->right->token->value));
						return node;
					}
					else if (var_list[var_name]->type == VarType::STRING)
					{
						node->token->type = StringToTokenType("STRING");
						int x = std::stoi(node->right->token->value);
						node->token->value = "";
						while (x) {
							node->token->value += var_list[var_name]->value ;
							--x;
						}
						return node;
					}
				}

		}
		else if (left == "NUMBER" && right == "VAR")
		{
			std::string var_name = node->right->token->value;
			bool found = false;
			size_t size = list_iter + 1;
				if (var_list.count(var_name))
				{
					found = true;
					if (var_list[var_name]->type == VarType::INT)
					{
						node->token->type = StringToTokenType("NUMBER");
						node->token->value = std::to_string(std::stoi(var_list[var_name]->value) * std::stoi(node->left->token->value));
						return node;
					}
				}
		}
		else if (left == "STRING" && right == "NUMBER")
		{
			node->token->type = StringToTokenType("STRING");
			int x = std::stoi(node->right->token->value);
			node->token->value = "";
			std::string str_tmp = node->left->token->value;
			while (x) {
				node->token->value += str_tmp;
				--x;
			}
			return node;
		}
	}
	else if (token_type == "DIV")
	{
		std::string left = TokenTypeSwitch(node->left->token->type);
		std::string right = TokenTypeSwitch(node->right->token->type);
		
	}
	else if (token_type == "IS_EQ")
	{
		std::string left = TokenTypeSwitch(node->left->token->type);
		std::string right = TokenTypeSwitch(node->right->token->type);

		if (left == "BOOL" && right == "BOOL")
		{
			node->token->type = StringToTokenType("BOOL");
			if (node->left->token->value == node->right->token->value)
			{
				node->token->value = "true";
			}
			else
				node->token->value = "false";
			return node;
		}
		else if (left == "VAR" && right == "VAR")
		{
			if (var_list[node->left->token->value]->type == VarType::BOOL && var_list[node->right->token->value]->type == VarType::BOOL) {
				node->token->type = StringToTokenType("BOOL");
				if (var_list[node->left->token->value]->value == var_list[node->right->token->value]->value)
				{
					node->token->value = "true";
				}
				else
					node->token->value = "false";
				return node;
			}
			else if (var_list[node->left->token->value]->type == VarType::INT && var_list[node->right->token->value]->type == VarType::INT) {
				node->token->type = StringToTokenType("BOOL");
				if (var_list[node->left->token->value]->value == var_list[node->right->token->value]->value)
				{
					node->token->value = "true";
				}
				else
					node->token->value = "false";
				return node;
			}
			else if (var_list[node->left->token->value]->type == VarType::STRING && var_list[node->right->token->value]->type == VarType::STRING) {
				node->token->type = StringToTokenType("BOOL");
				if (var_list[node->left->token->value]->value == var_list[node->right->token->value]->value)
				{
					node->token->value = "true";
				}
				else
					node->token->value = "false";
				return node;
			}
			else
			{
				std::cout << "Error: is equal!\n";
				system("pasue");
			}

		}
		else if (left == "NUMBER" && right == "NUMBER")
		{
			node->token->type = StringToTokenType("BOOL");
			if (node->left->token->value == node->right->token->value)
			{
				node->token->value = "true";
			}
			else
				node->token->value = "false";
			return node;
		}
		else if (left == "STRING" && right == "STRING")
		{
			node->token->type = StringToTokenType("BOOL");
			if (node->left->token->value == node->right->token->value)
			{
				node->token->value = "true";
			}
			else
				node->token->value = "false";
			return node;
		}
		else
		{
			std::cout << "Error: is equal!\n";
			system("pasue");
		}

	}
}

VarType VarCreator::TypeInit(std::shared_ptr<NodeAST> node)
{
	std::string type = TokenTypeSwitch(node->token->type);

	if (type == "NUMBER")
		return VarType::INT;
	else if (type == "STRING")
		return VarType::STRING;
	else if (type == "TRUE")
		return VarType::BOOL;
	else if (type == "FALSE")
		return VarType::BOOL;
	else if (type == "BOOL")
		return VarType::BOOL;
	else {
		std::cout << "Error: var type has not idintified!\n";
		system("pause");
	}
}