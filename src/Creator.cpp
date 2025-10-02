#include"../include/Creator.h"

void ObjectCreator::CreateObject(Creator* creator, std::shared_ptr<NodeAST> node, size_t node_iter)
{
	creator->CreateObject(node, node_iter);
	delete creator;
}

void VarCreator::CreateObject(std::shared_ptr<NodeAST> node, size_t node_iter)
{
	op_manager->DoOperation(node->right);
	std::shared_ptr<Variable> tmp = std::make_shared<Variable>()
}

BasicVarType VarTypeSelector(std::shared_ptr<NodeAST> node)
{
	TokenType 
	if()
}