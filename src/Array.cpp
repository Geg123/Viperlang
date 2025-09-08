#include"../include/Var.h"

Array::Array(std::string _name):name(_name){}

void ArrayCreator::CreateArray(std::shared_ptr<NodeAST> node_eq)
{
	std::shared_ptr<NodeAST> iter;

	std::string arr_name = node_eq->left->token->value;

	std::shared_ptr<Array> curr_arr;

	iter = node_eq->right;

	size_t size = list_of_arrays.size();
		if (list_of_arrays.count(arr_name))
		{
			curr_arr = list_of_arrays[arr_name];
			curr_arr->array.clear();
			size_t j = 0;
			Variable var("tmp");

			while (1)
			{
				if (iter->right == nullptr)
					break;
				var.value = iter->right->token->value;
				std::string type = TokenTypeSwitch(iter->right->token->type);

				if (type == "NUMBER")
					var.type = StringToVarType("INT");
				else if (type == "STRING")
					var.type = StringToVarType("STRING");
				else {
					std::cout << "Error: var type in array " << arr_name << " on index " << j << " has not idintified!\n";
					system("pause");
				}
				++j;
				iter = iter->right;
				curr_arr->array.push_back(var);
			}
			return;
		}
		else if (var_crt->var_list.count(arr_name))
		{
			var_crt->var_list.erase(arr_name);
		}
	curr_arr = std::make_shared<Array>(arr_name);


	size_t j = 0;
	Variable tmp("tmp");
	while (1)
	{
		if (iter->right == nullptr)
			break;
		tmp.value = iter->right->token->value;
		std::string type = TokenTypeSwitch(iter->right->token->type);

		if (type == "NUMBER")
			tmp.type = StringToVarType("INT");
		else if (type == "STRING")
			tmp.type = StringToVarType("STRING");
		else {
			std::cout << "Error: var type in array " << arr_name << " on index " << j << " has not idintified!\n";
			system("pause");
		}
		++j;
		iter = iter->right;
		curr_arr->array.push_back(tmp);
	}
	
	list_of_arrays[arr_name] = curr_arr;
	return;
}

Variable ArrayCreator::setArrIndex(std::shared_ptr<NodeAST> node_index) { return NULL; }