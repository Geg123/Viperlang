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
	ObjectManager::InsertObject(tmp);
}

void ArrayCreator::CreateObject(std::shared_ptr<NodeAST> root)
{
	//std::shared_ptr<Array> array = std::
	std::shared_ptr<NodeAST> node = root->left;

}