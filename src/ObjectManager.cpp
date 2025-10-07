#include"../include/ObjectManager.h"

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

void ObjectManager::Create(std::shared_ptr<NodeAST> node, size_t iterator)
{
    //TokenType type = node->right->token->type;
    //std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> _objects = std::make_shared<std::unordered_map<std::string, std::shared_ptr<Object>>>(objects);

    //std::shared_ptr<OperatorsManager> tmpOpMan = std::make_shared<OperatorsManager>(std::make_shared<std::unordered_map<std::string, std::shared_ptr<Object>>>(objects));
    std::shared_ptr<OperatorsManager> tmpOpMan = std::make_shared<OperatorsManager>(ObjCreator->objects);

    if(node->token->type == TokenType::FUNC_INIT)
    {
        //ObjCreator->CreateObject(new FuncCreator(tmpOpMan), node, iterator);
    }
    else if(operators.count(node->right->token->type))
    {
        ObjCreator->CreateObject(new VarCreator(tmpOpMan), node, iterator);
    }
    else if(node->right->token->type == TokenType::ARR_LIST)
    {
        //ObjCreator->CreateObject(new ArrayCreator(tmpOpMan), node, iterator);
    }
}