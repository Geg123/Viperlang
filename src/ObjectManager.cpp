#include"../include/ObjectManager.h"

std::unordered_set<TokenType> types{ TokenType::NUMBER, TokenType::STRING, TokenType::VAR, TokenType::INT, TokenType::INPUT };

ObjectManager* ObjectManager::getInstance()
{
    if(manager == nullptr)
    {
        manager = new ObjectManager;
    }
    return manager;
}

ObjectManager::~ObjectManager()
{
    delete manager;
}

void ObjectManager::InsertObject(std::shared_ptr<Object> obj)
{
    objects.insert({obj->name, obj});
}

std::shared_ptr<Object> ObjectManager::getObject(std::string name)
{
    if(objects.count(name))
    {
        return objects.at(name);
    }
    else
    {
        return nullptr;
    }
}