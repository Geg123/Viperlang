#include"../include/Operators.h"

NodeAST copyNodeTo(std::shared_ptr<NodeAST> node)
{
	NodeAST res(std::make_shared<Token>(node->token->type, node->token->value));
	if(node->left != nullptr)
	{
		res.left = std::make_shared<NodeAST>(copyNodeTo(node->left));
	}
	if(node->right != nullptr)
	{
		res.right = std::make_shared<NodeAST>(copyNodeTo(node->right));
	}
	return res;
}

BasicVarType VarTypeSelector(std::shared_ptr<NodeAST> node)
{
	TokenType type = node->token->type;
	if(type == TokenType::NUMBER)
		return BasicVarType::INT;
	else if(type == TokenType::STRING)
		return BasicVarType::STRING;
	else if(type == TokenType::BOOL)
		return BasicVarType::BOOL;
	else if(type == TokenType::FALSE)
		return BasicVarType::BOOL;
	else if(type == TokenType::TRUE)
		return BasicVarType::BOOL;
}

void FuncCreator::CreateObject(std::shared_ptr<NodeAST> node, size_t& node_iter)
{
	if(ObjectManager::isObject(node->token->value))
	{
		std::cerr << "Error: " << node->token->value << "has already defenited!";
        system("pause");
	}
	Function func(node->token->value);
	++node_iter;
	while(Parser::line_nodes.at(node_iter)->token->type != TokenType::FUNC_END)
	{
		func.definition_nodes.push_back(copyNodeTo(Parser::line_nodes.at(node_iter)));
		++node_iter;
	}
	size_t i = 0;
	while(node->right != nullptr)
	{
		node = node->right;
		func.def_vars.insert({i, node->token->value});
		++i;
	}
	ObjectManager::InsertObject(std::make_shared<Function>(func));
}

void VarCreator::CreateObject(std::shared_ptr<NodeAST> node)
{
	OperatorsManager::DoOperation(node->right);
	std::shared_ptr<Variable> tmp = std::make_shared<Variable>(node->left->token->value, node->right->token->value);
	tmp->type = VarTypeSelector(node->right);
	ObjectManager::deleteObject(node->left->token->value);
	ObjectManager::InsertObject(tmp);
}

void ArrayCreator::CreateObject(std::shared_ptr<NodeAST> node)
{
	std::shared_ptr<Array> array = std::make_shared<Array>(node->left->token->value);
	std::shared_ptr<NodeAST> root = node->right;
	size_t iter = 0;
	while(root->left != nullptr)
	{
		root = root->left;
		OperatorsManager::DoOperation(root->right);
		array->array.push_back(std::make_shared<Variable>(std::to_string(iter), root->right->token->value));
		std::get<std::shared_ptr<Variable>>(array->array[iter])->type = VarTypeSelector(root->right);
		++iter;
	}
	ObjectManager::deleteObject(node->left->token->value);
	ObjectManager::InsertObject(array);
}