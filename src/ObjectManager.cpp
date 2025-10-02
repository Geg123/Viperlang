#include"../include/Objects.h"

ObjectManager::ObjectManager()
{
    ObjCreator = std::make_shared<ObjectCreator>(objects);
}

void ObjectManager::Create(std::shared_ptr<NodeAST> node, size_t iterator)
{
    TokenType type = node->right->token->type;
    //std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> _objects = std::make_shared<std::unordered_map<std::string, std::shared_ptr<Object>>>(objects);

    std::shared_ptr<OperatorsManager> tmpOpMan = std::make_shared<OperatorsManager>(objects);

    if(type == TokenType::FUNC_INIT)
    {
        ObjCreator->CreateObject(new FuncCreator(tmpOpMan), node, iterator);
    }
    else if(operators.count(type))
    {
        ObjCreator->CreateObject(new VarCreator(tmpOpMan), node, iterator);
    }
    else if(type == TokenType::ARR_LIST)
    {
        ObjCreator->CreateObject(new ArrayCreator(tmpOpMan), node, iterator);
    }
}