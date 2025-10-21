#include"../include/Creator.h"

void CreateObject(Creator* creator, std::shared_ptr<NodeAST> node, size_t node_iter, std::shared_ptr<std::vector<std::shared_ptr<NodeAST>>> line_nodes)
{
	creator->CreateObject(node, node_iter, line_nodes);
	delete creator;
}

void FuncCreator::CreateObject(std::shared_ptr<NodeAST> node, size_t node_iter, std::shared_ptr<std::vector<std::shared_ptr<NodeAST>>> line_nodes)
{
	Function func(node->token->value);
	++node_iter;
	size_t i = 0;
	while(line_nodes->at(node_iter)->token->type != TokenType::FUNC_END)
	{
		func.definition_nodes[i] = *line_nodes->at(node_iter);
		++node_iter;
		++i;
	}
	while(node->right != nullptr)
	{
		node = node->right;
		func.def_vars.insert(node->token->value);
	}
	obj_manager->InsertObject(std::make_shared<Object>(func));
}

void VarCreator::CreateObject(std::shared_ptr<NodeAST> node, size_t node_iter, std::shared_ptr<std::vector<std::shared_ptr<NodeAST>>> line_nodes)
{
	op_manager->DoOperation(node->right);
	std::shared_ptr<Variable> tmp = std::make_shared<Variable>(node->left->token->value, node->right->token->value);
	tmp->type = VarTypeSelector(node->right);
	obj_manager->InsertObject(tmp);
}

BasicVarType Creator::VarTypeSelector(std::shared_ptr<NodeAST> node)
{
	TokenType type = node->token->type;
	if(type == TokenType::NUMBER)
		return BasicVarType::INT;
	else if(type == TokenType::STRING)
		return BasicVarType::STRING;
	else if(type == TokenType::BOOL)
		return BasicVarType::BOOL;
}