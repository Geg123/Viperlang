#include"../include/Creator.h"

void ObjectCreator::CreateObject(Creator* creator, std::shared_ptr<NodeAST> node, size_t node_iter)
{
	creator->CreateObject(node, node_iter);
	delete creator;
}


void VarCreator::CreateObject(std::shared_ptr<NodeAST> node, size_t node_iter)
{
	op_manager->DoOperation(node->right);
	std::shared_ptr<Variable> tmp = std::make_shared<Variable>(node->left->token->value, node->right->token->value);
	tmp->type = VarTypeSelector(node->right);
	op_manager->InsertObject(tmp);
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