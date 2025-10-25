#include"../include/ObjectManager.h"

TokenType BasicVarTypeToType(BasicVarType type)
{ 
	if(type == BasicVarType::INT)
        return TokenType::INT;
    else if(type == BasicVarType::STRING)
	    return TokenType::STRING;
    else if(type == BasicVarType::BOOL)
	    return TokenType::BOOL;
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
    auto ptr = std::get_if<std::shared_ptr<Array>>(&obj);
    if(ptr != nullptr)
    {
        objects->insert({(*ptr)->name, *ptr});
        return;
    }
    auto ptr = std::get_if<std::shared_ptr<Function>>(&obj);
    if(ptr != nullptr)
    {
        objects->insert({(*ptr)->name, *ptr});
        return;
    }
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
    if(!objects->count(name))
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
}

void ObjectManager::run_func(std::shared_ptr<NodeAST> node, std::shared_ptr<Function> funcptr)
{
    Function func("func" + std::to_string(ObjectManager::func_iter));
    ObjectManager::incrementIter();
    func.def_vars = funcptr->def_vars;
    size_t iter = 0;
    for(auto tmp : funcptr->definition_nodes)
	{
		func.definition_nodes.push_back(copyNodeTo(std::make_shared<NodeAST>(tmp)));
	}
    size_t def_vars_lenght = funcptr->def_vars.size();
    for(size_t i = 0; i < def_vars_lenght; ++i)
    {
        if(node->right != nullptr)
        {
            node = node->right;
            Variable tmp(func.def_vars.at(i));
            CalcExpr(node);
            tmp.value = node->token->value;
            scopes.at(func.name).insert({tmp.name, std::make_shared<Variable>(tmp)});
        }
        else
        {
            std::cerr << "Error: function call has't same quantity parametrs as defeniyion!";
            system("pause");
        }
    }

    func.definition_nodes = funcptr->definition_nodes;
    ObjectManager::setScope(func.name);
    size_t lenght = funcptr->definition_nodes.size();
    for(size_t i = 0; i < lenght; ++i)
    {
        TokenType type = Parser::line_nodes[i]->token->type;
		if(type == TokenType::EQ)
		{
			var_crt.CreateObject(parser.line_nodes[i]);
		}
		else if(type == TokenType::FUNCTION)
		{
			
		}
		else if(type == TokenType::FUNC_INIT)
		{

		}
		else if(type == TokenType::PRINT)
		{
			std::cout << CalcExpr(parser.line_nodes[i]->right)->token->value << "\n";
		}
    }
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