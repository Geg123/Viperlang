#include"../include/ObjectManager.h"

std::unordered_set<TokenType> types{ TokenType::NUMBER, TokenType::STRING, TokenType::VAR, TokenType::INT, TokenType::INPUT };

ObjectManager::ObjectManager()
{
    ObjCreator = std::make_shared<ObjectCreator>(std::make_shared<std::unordered_map<std::string, std::shared_ptr<Object>>>(objects));
}

std::shared_ptr<NodeAST> ObjectManager::CalcExpr(std::shared_ptr<NodeAST> node)
{
    std::shared_ptr<OperatorsManager> tmpOpMan = std::make_shared<OperatorsManager>(ObjCreator->objects);

    tmpOpMan->DoOperation(node);
    return node;
}

void ObjectManager::Create(std::shared_ptr<NodeAST> node, size_t iterator, std::shared_ptr<std::vector<std::shared_ptr<NodeAST>>> line_nodes)
{
    //TokenType type = node->right->token->type;
    //std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> _objects = std::make_shared<std::unordered_map<std::string, std::shared_ptr<Object>>>(objects);

    //std::shared_ptr<OperatorsManager> tmpOpMan = std::make_shared<OperatorsManager>(std::make_shared<std::unordered_map<std::string, std::shared_ptr<Object>>>(objects));
    std::shared_ptr<OperatorsManager> tmpOpMan = std::make_shared<OperatorsManager>(ObjCreator->objects);

    if(node->token->type == TokenType::FUNC_INIT)
    {
        ObjCreator->CreateObject(new FuncCreator(tmpOpMan), node, iterator, line_nodes);
    }
    else if(operators.count(node->right->token->type) || types.count(node->right->token->type))
    {
        ObjCreator->CreateObject(new VarCreator(tmpOpMan), node, iterator, nullptr);
    }
    else if(node->right->token->type == TokenType::ARR_LIST)
    {
        //ObjCreator->CreateObject(new ArrayCreator(tmpOpMan), node, iterator);
    }
}

std::shared_ptr<NodeAST> copyNode(std::shared_ptr<NodeAST> node)
{
    std::shared_ptr<NodeAST> new_node;
    new_node->token->type = node->token->type;
    new_node->token->value = node->token->value;
    while(node->right != nullptr)
    {
        node = node->right;
        new_node = new_node->right;
        new_node->token->type = node->token->type;
        new_node->token->value = node->token->value;
    }
    return new_node;
}

void ExecuteFunc()
{
    std::vector<std::shared_ptr<NodeAST>> func_nodes;

    size_t i = 0;
    for(auto tmp : func_nodes)
    {
        
    }

    size_t size = func_nodes.line_nodes.size();
	for(size_t i = 0; i < size; ++i)
	{
		TokenType type = parser.line_nodes[i]->token->type;
		if(type == TokenType::EQ || type == TokenType::FUNC_INIT)
		{
			objManager.Create(parser.line_nodes[i], i, std::make_shared<std::vector<std::shared_ptr<NodeAST>>>(parser.line_nodes));
		}
		else if(type == TokenType::FUNCTION)
		{
			if(objManager.isObjectFunc(parser.line_nodes[i]->token->value))
			{
				ExecuteFunc(objManager.getFunc(parser.line_nodes[i]->token->value));
			}	
		}
		else if(type == TokenType::PRINT)
		{
			std::cout << objManager.CalcExpr(parser.line_nodes[i]->right)->token->value << "\n";
		}
	}
}

std::shared_ptr<Function> ObjectManager::getFunc(std::string name)
{
    return std::make_shared<Function>(dynamic_cast<Function*>(objects.at(name).get()));
}

bool ObjectManager::isObjectFunc(std::string name)
{
    if(objects.count(name))
    {
        try
        {
            NodeAST tmp = *dynamic_cast<Function*>(objects.at(name).get())->definition_nodes[0].get();
        }
        catch(...)
        {
            return false;
        }
        return true;
    }
    else
    {
        return false;
    }
}