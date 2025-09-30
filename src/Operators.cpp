#include"../include/Operators.h"

Type* OperatorsManager::TokenTypeToType(std::shared_ptr<NodeAST> node)
{
    
}

void OperatorsManager::DoOperation(std::shared_ptr<NodeAST> node)
{
    Type* type = TokenTypeToType(node);
    Operator* op = NodeTypeToOperator(node);
    type;
    delete type;
}

Operator* OperatorsManager::NodeTypeToOperator(std::shared_ptr<NodeAST> node)
{
    int type = int(node->token->type);
    switch (type)
    {
    case 1: return new EqOperator;
    case 2: return new PlusOperator;
	case 3: return new MinusOperator;
    case 11: return new NotOperator;
	case 12: return new IsEqOperator;
	case 13: return new NotEqOperator;
    case 17: return new MultOperator;
	case 18: return new DivOperator;
    case 28: return new GreaterOperator;
	case 29: return new LessOperator;
	case 30: return new AndOperator;
	case 31: return new OrOperator;
    }
}