#include"../include/ObjectManager.h"

TokenType BasicVarTypeToType(BasicVarType type)
{ 
	if(type == BasicVarType::INT)
        return TokenType::NUMBER;
    else if(type == BasicVarType::STRING)
	    return TokenType::STRING;
    else if(type == BasicVarType::BOOL)
	    return TokenType::BOOL;
}

BasicVarType TokenTypeToBasicVarType(TokenType type)
{
    if (type == TokenType::NUMBER)
        return BasicVarType::INT;
    else if (type == TokenType::STRING)
        return BasicVarType::STRING;
    else if (type == TokenType::BOOL || type == TokenType::FALSE || type == TokenType::TRUE)
        return BasicVarType::BOOL;
}

std::unordered_set<TokenType> types{ TokenType::NUMBER, TokenType::STRING, TokenType::VAR, TokenType::INT, TokenType::INPUT };

void ObjectManager::InsertObject(Object obj)
{
    auto ptr = std::get_if<std::shared_ptr<Variable>>(&obj);
    if(ptr != nullptr)
    {
        objects->insert({(*ptr)->name, *ptr});
        return;
    }
    auto ptr2 = std::get_if<std::shared_ptr<Array>>(&obj);
    if(ptr2 != nullptr)
    {
        objects->insert({(*ptr2)->name, *ptr2});
        return;
    }
    auto ptr3 = std::get_if<std::shared_ptr<Function>>(&obj);
    if(ptr3 != nullptr)
    {
        objects->insert({(*ptr3)->name, *ptr3});
        return;
    }
}

bool ObjectManager::isObject(std::string name)
{
    if(objects->count(name))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ObjectManager::deleteObject(std::string name)
{
    if(objects->count(name))
        objects->erase(name);
}

Object ObjectManager::getObject(std::string name)
{
    if(objects->count(name))
    {
        return objects->at(name);
    }
    else
    {
        return nullptr;
    }
}

void ObjectManager::getValue(std::shared_ptr<NodeAST> node)
{
    std::string name = node->token->value;
    if(name == "input")
    {
        if(node->right != nullptr)
            std::cout << node->right->token->value;
        node->token->value = input();
        node->token->type = TokenType::STRING;
    }
    else if(!objects->count(name))
    {
        std::cerr << "Error: " << name << " is not a Object!";
        system("pause");
        return;
    }

    if(node->token->type == TokenType::FUNCTION)
    {
        auto func = *std::get_if<std::shared_ptr<Function>>(&objects->at(name));
        if(func != nullptr)
        {
            run_func(node, func);
            return;
        }
        std::cerr << "Error: " << name << " is not a Function!";
        system("pause");
    }
    else if(node->token->type == TokenType::VAR)
    {
        auto tmp = *std::get_if<std::shared_ptr<Variable>>(&objects->at(name));
        if(tmp != nullptr)
        {
            node->token->value = tmp->value;
            node->token->type = BasicVarTypeToType(tmp->type);
            return;
        }
        std::cerr << "Error: " << name << " is not a Variable!";
        system("pause");
    }
    else if(node->token->type == TokenType::ARRAY)
    {
        auto tmp = *std::get_if<std::shared_ptr<Array>>(&objects->at(name));
        if(tmp != nullptr)
        {
            CalcExpr(node->right);
            int i = std::stoi(node->right->token->value);
            if(tmp->array.size() > i)
            {
                auto tmp2 = std::get<std::shared_ptr<Variable>>(tmp->array[i]);
                node->token->value = tmp2->value;
                node->token->type = BasicVarTypeToType(tmp2->type);
                return;
            }
        }
        std::cerr << "Error: " << name << " is not a Array!";
        system("pause");
    }
    
}

void ObjectManager::run_func(std::shared_ptr<NodeAST> node, std::shared_ptr<Function> funcptr)
{
    Function func("func" + std::to_string(func_iter++));
    //incrementIter();
    func.def_vars = funcptr->def_vars;
    size_t iter = 0;
    for(auto tmp : funcptr->definition_nodes)
	{
		func.definition_nodes.push_back(copyNodeTo(std::make_shared<NodeAST>(tmp)));
	}
    size_t def_vars_lenght = funcptr->def_vars.size();
    std::unordered_map<std::string, Object> tmp_map;
    scopes.insert({ func.name, tmp_map });
    std::shared_ptr<NodeAST> node2 = node;
    for(size_t i = 0; i < def_vars_lenght; ++i)
    {
        if(node2->left != nullptr)
        {
            node2 = node2->left;
            Variable tmp(func.def_vars.at(i));
            CalcExpr(node2->right);
            tmp.value = node2->right->token->value;
            tmp.type = TokenTypeToBasicVarType(node2->right->token->type);
            Object tmp_obj = std::make_shared<Variable>(tmp);
            scopes.at(func.name).insert({ tmp.name, tmp_obj });
        }
        else
        {
            std::cerr << "Error: function call has't same quantity parametrs as defeniyion!\n";
            system("pause");
        }
    }
    scopes.at(func.name).insert({funcptr->name,objects->at(funcptr->name)});
    setScope(func.name);
    pushScopeStack(func.name);
    size_t lenght = funcptr->definition_nodes.size();
    VarCreator var_crt;
	FuncCreator func_crt;
	ArrayCreator arr_crt;
    for(size_t i = 0; i < lenght; ++i)
    {
        std::shared_ptr<NodeAST> _node = std::make_shared<NodeAST>(func.definition_nodes[i]);
        TokenType type = _node->token->type;
		if(type == TokenType::EQ)
		{
			var_crt.CreateObject(_node);
		}
		else if(type == TokenType::FUNCTION)
		{
			getValue(_node);
		}
		else if(type == TokenType::FUNC_INIT)
		{
            func_crt.CreateObject(_node, i);
		}
		else if(type == TokenType::PRINT)
		{
            CalcExpr(_node->right);
			std::cout << _node->right->token->value << "\n";
		}
        else if(type == TokenType::RETURN)
		{
			ObjectManager::CalcExpr(_node->right);
            node->token->value = _node->right->token->value;
            node->token->type = _node->right->token->type;
            break;
		}
        else if (type == TokenType::IF)
        {
            CalcExpr(_node->right);
            ToBool(_node->right);
            if (_node->right->token->value == "False")
            {
                ++i;
                size_t counter = 0;
                while (true)
                {
                    TokenType type = func.definition_nodes[i].token->type;
                    if (type == TokenType::IF)
                        ++counter;
                    else if (type == TokenType::IF_END && counter != 0)
                        --counter;
                    else if (type == TokenType::IF_END && counter == 0 || type == TokenType::FUNC_END || type == TokenType::END)
                        break;
                    ++i;
                }
            }
        }
    }
    popScopeStack();
    setScope(getTopScopeStack());
    --func_iter;
    scopes.erase(func.name);
}

std::string ObjectManager::input()
{
    std::string tmp;
    std::getline(std::cin, tmp);
    return tmp;
}

void ObjectManager::setScope(std::string name)
{
    if(name == "global")
    {
        objects = &global;
    }
    else
    {
        objects = &scopes.at(name);
    }
}