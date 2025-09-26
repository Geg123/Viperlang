#include"../include/Operators.h"

void OperatorsManager::DoOperation(std::shared_ptr<NodeAST> node, Operator* type)
{
    type->operation(node);
    delete type;
}

Operator* TokenTypeToOperator(std::shared_ptr<NodeAST> node)
{
    int type = int(node->token->type);
    switch (type)
    {
    case 0:
        break;
    
    default:
        break;
    }
}