#include"../include/Operators.h"
#include<cmath>
std::unordered_set<TokenType> operators{ TokenType::PLUS, TokenType::MINUS, TokenType::MULT, TokenType::DIV, TokenType::MODULE, TokenType::AND, TokenType::OR, TokenType::IS_EQ, TokenType::NOT, TokenType::NOT_EQ, TokenType::POWER};

OperatorsManager::OperatorsManager(std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> _objects)
{
    objects = _objects;
}

Type* TokenTypeToTypeSwitcher(TokenType left, TokenType right)
{
	if(left == TokenType::STRING || right == TokenType::STRING)
        return new String;
    else if(left == TokenType::NUMBER || right == TokenType::NUMBER)
	    return new Int;
    else if (left == TokenType::INT || right == TokenType::INT)
        return new Int;
    else if(left == TokenType::BOOL || right == TokenType::BOOL)
	    return new Bool;
    else if (left == TokenType::FALSE || right == TokenType::FALSE)
        return new Bool;
    else if (left == TokenType::TRUE || right == TokenType::TRUE)
        return new Bool;
}

TokenType BasicVarTypeToType(BasicVarType type)
{ 
	if(type == BasicVarType::INT)
        return TokenType::INT;
    else if(type == BasicVarType::STRING)
	    return TokenType::STRING;
    else if(type == BasicVarType::BOOL)
	    return TokenType::STRING;
}

void OperatorsManager::InsertObject(std::shared_ptr<Object> obj)
{
    objects->insert({obj->name, obj});
}
   
Type* OperatorsManager::TokenTypeToType(std::shared_ptr<NodeAST> node)
{
    TokenType left;
    TokenType right;
    BasicVarType var_type = BasicVarType::BOOL;
    if(node->left == nullptr && node->right == nullptr)
    {
        if(node->token->type == TokenType::VAR)
        {
            return TokenTypeToTypeSwitcher(BasicVarTypeToType(dynamic_cast<Variable*>(objects->at(node->token->value).get())->type), TokenType::AND);
        }
        TokenType type = node->token->type;
        return TokenTypeToTypeSwitcher(type, TokenType::AND);
    }
    if(node->left != nullptr)
    {
        left = node->left->token->type;
    }
    if(node->right != nullptr)
    {
        right = node->right->token->type;
    }
    if(operators.count(left) || operators.count(right))
    {
        return new NotFullType;
    }
    if(left == TokenType::VAR)
    {
        std::string tmp_var_name = node->left->token->value;
        if(objects->count(tmp_var_name))
        {
            BasicVarType tmp_var_type;
            try
            {
                tmp_var_type = dynamic_cast<Variable*>(objects->at(tmp_var_name).get())->type;
            }
            catch(...)
            {
                std::cerr << "Error: "<< tmp_var_name << " is not a variable!\n";
                system("pause");
            }
            left = BasicVarTypeToType(tmp_var_type);
        }
        else 
        {
            std::cerr << "Error: var " << tmp_var_name << " doesn't exist!\n";
            system("pause");
        }
    }
    if(right == TokenType::VAR)
    {
        std::string tmp_var_name = node->right->token->value;
        if(objects->count(tmp_var_name))
        {
            BasicVarType tmp_var_type;
            try
            {
                tmp_var_type = dynamic_cast<Variable*>(objects->at(tmp_var_name).get())->type;
            }
            catch(...)
            {
                std::cerr << "Error: "<< tmp_var_name << " is not a variable!\n";
                system("pause");
            }
            right = BasicVarTypeToType(tmp_var_type);
        }
        else 
        {
            std::cerr << "Error: var " << tmp_var_name << " doesn't exist!\n";
            system("pause");
        }
    }
    return TokenTypeToTypeSwitcher(left , right);
}

void OperatorsManager::DoOperation(std::shared_ptr<NodeAST> node)
{
    Type* type = TokenTypeToType(node);
    if(!type->test())
    {
        DoOperation(node->left);
        DoOperation(node->right);
    }
    type = TokenTypeToType(node);
    TypeOperations op = NodeTypeToOperator(node);
    type->executeOperation(node, op, objects);
    delete type;
}

TypeOperations OperatorsManager::NodeTypeToOperator(std::shared_ptr<NodeAST> node)
{
    TypeOperations a;
    int type = int(node->token->type);
    switch (type)
    {
    case 1: return a = EqOperator{};
    case 2: return a = PlusOperator{};
    case 3: return a = MinusOperator{};
    case 11: return a = NotOperator{};
    case 12: return a = IsEqOperator{};
    case 13: return a = NotEqOperator{};
    case 17: return a = MultOperator{};
    case 18: return a = DivOperator{};
    case 28: return a = GreaterOperator{};
    case 29: return a = LessOperator{};
    case 30: return a = AndOperator{};
    case 31: return a = OrOperator{};
    case 44: return a = PowerOperator{};
    }
    return EqOperator{};
}

void Bool::executeOperation(std::shared_ptr<NodeAST> node, TypeOperations op, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> _objects)
{
    std::visit(Functor(node, _objects), op);
}

void Bool::Functor::operator()(IsEqOperator& op)
{
    if(node->left->token->value == node->right->token->value)
    {
        node->token->value = "True";
    }
    else 
    {
        node->token->value = "False";
        
    }
    node->token->type = TokenType::BOOL;
}

void Bool::Functor::operator()(AndOperator& op)
{
    if(node->left->token->value == node->right->token->value)
    {
        node->token->value = "True";
        
    }
    else 
    {
        node->token->value = "False";
        
    }
    node->token->type = TokenType::BOOL;
}

void Bool::Functor::operator()(OrOperator& op)
{
    if(node->left->token->value == "True" || node->right->token->value == "True")
    {
        node->token->value = "True";
        
    }
    else 
    {
        node->token->value = "False";
        
    }
    node->token->type = TokenType::BOOL;
}

void Bool::Functor::operator()(NotEqOperator& op)
{
    if(node->left->token->value != node->right->token->value)
    {
        node->token->value = "True";
        
    }
    else 
    {
        node->token->value = "False";
        
    }
    node->token->type = TokenType::BOOL;
}

void Bool::Functor::operator()(EqOperator& op)
{
    if(node->token->type == TokenType::VAR)
    {
        node->token->value = dynamic_cast<Variable*>(objects->at(node->token->value).get())->value;
    }
    node->token->type = TokenType::BOOL;
}

void Int::executeOperation(std::shared_ptr<NodeAST> node, TypeOperations op, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> _objects)
{
    std::visit(Functor(node, _objects), op);
}

void Int::Functor::getVars()
{
    if (node->left->token->type == TokenType::VAR)
    {
        node->left->token->type = BasicVarTypeToType(dynamic_cast<Variable*>(objects->at(node->left->token->value).get())->type);
        node->left->token->value = dynamic_cast<Variable*>(objects->at(node->left->token->value).get())->value;
    }
    if (node->right->token->type == TokenType::VAR)
    {
        node->right->token->type = BasicVarTypeToType(dynamic_cast<Variable*>(objects->at(node->right->token->value).get())->type);
        node->right->token->value = dynamic_cast<Variable*>(objects->at(node->right->token->value).get())->value;
    }
}

void Int::Functor::operator()(IsEqOperator& op)
{
    getVars();
    if(std::stoi(node->left->token->value) == std::stoi(node->right->token->value))
    {
        node->token->value = "True";
    }
    else 
    {
        node->token->value = "False";
    }
    node->token->type = TokenType::BOOL;
}

void Int::Functor::operator()(NotEqOperator& op)
{
    getVars();
    if(std::stoi(node->left->token->value) != std::stoi(node->right->token->value))
    {
        node->token->value = "True";
    }
    else 
    {
        node->token->value = "False";
    }
    node->token->type = TokenType::BOOL;
}

void Int::Functor::operator()(GreaterOperator& op)
{
    getVars();
    if(std::stoi(node->left->token->value) > std::stoi(node->right->token->value))
    {
        node->token->value = "True";
    }
    else 
    {
        node->token->value = "False";
    }
    node->token->type = TokenType::BOOL;
}

void Int::Functor::operator()(LessOperator& op)
{
    getVars();
    if(std::stoi(node->left->token->value) < std::stoi(node->right->token->value))
    {
        node->token->value = "True";
    }
    else 
    {
        node->token->value = "False";
    }
    node->token->type = TokenType::BOOL;
}

void Int::Functor::operator()(PlusOperator& op)
{
    getVars();
    node->token->value = std::to_string(std::stoi(node->left->token->value) + std::stoi(node->right->token->value));
    node->token->type = TokenType::INT;
}

void Int::Functor::operator()(MinusOperator& op)
{
    getVars();
    node->token->value = std::to_string(std::stoi(node->left->token->value) - std::stoi(node->right->token->value));
    node->token->type = TokenType::INT;
}

void Int::Functor::operator()(MultOperator& op)
{
    getVars();
    node->token->value = std::to_string(std::stoi(node->left->token->value) * std::stoi(node->right->token->value));
    node->token->type = TokenType::INT;
}

void Int::Functor::operator()(DivOperator& op)
{
    getVars();
    if(std::stoi(node->right->token->value) == 0)
    {
        std::cerr << "Error: you can't divide by zero!\n";
        system("pause");
    }
    node->token->value = std::to_string(std::stoi(node->left->token->value) / std::stoi(node->right->token->value));
    node->token->type = TokenType::INT;
}

void Int::Functor::operator()(PowerOperator& op)
{
    getVars();
    node->token->value = std::to_string(int(pow(std::stoi(node->left->token->value), std::stoi(node->right->token->value))));
    node->token->type = TokenType::INT;
}

void Int::Functor::operator()(EqOperator& op)
{
    if(node->token->type == TokenType::VAR)
    {
        node->token->value = dynamic_cast<Variable*>(objects->at(node->token->value).get())->value;
    }
    node->token->type = TokenType::INT;
}

void String::executeOperation(std::shared_ptr<NodeAST> node, TypeOperations op, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> _objects)
{
    std::visit(Functor(node, _objects), op);
}

void String::Functor::getVars()
{
    if (node->left->token->type == TokenType::VAR)
    {
        node->left->token->type = BasicVarTypeToType(dynamic_cast<Variable*>(objects->at(node->left->token->value).get())->type);
        node->left->token->value = dynamic_cast<Variable*>(objects->at(node->left->token->value).get())->value;
    }
    if (node->right->token->type == TokenType::VAR)
    {
        node->right->token->type = BasicVarTypeToType(dynamic_cast<Variable*>(objects->at(node->right->token->value).get())->type);
        node->right->token->value = dynamic_cast<Variable*>(objects->at(node->right->token->value).get())->value;
    }
}

void String::Functor::operator()(EqOperator& op)
{
    if(node->token->type == TokenType::VAR)
    {
        node->token->value = dynamic_cast<Variable*>(objects->at(node->token->value).get())->value;
    }
    node->token->type = TokenType::STRING;
}

void String::Functor::operator()(PlusOperator& op)
{
    getVars();
    node->token->value = node->left->token->value + node->right->token->value;
    node->token->type = TokenType::INT;
}

void String::Functor::operator()(MultOperator& op)
{
    getVars();
    if((node->left->token->type == TokenType::STRING && node->right->token->type == TokenType::NUMBER) || (node->left->token->type == TokenType::STRING && node->right->token->type == TokenType::INT))
    {
        int i = std::stoi(node->right->token->value);
        std::string tmp_str = node->left->token->value;
        node->left->token->value = "";
        node->token->value = "";
        while (i)
        {
            node->token->value += tmp_str;
            --i;
        }
        node->token->type = TokenType::STRING;
    }
    else if ((node->left->token->type == TokenType::NUMBER && node->right->token->type == TokenType::STRING) || (node->left->token->type == TokenType::INT && node->right->token->type == TokenType::STRING))
    {
        int i = std::stoi(node->left->token->value);
        std::string tmp_str = node->right->token->value;
        node->right->token->value = "";
        while (i)
        {
            node->token->value += tmp_str;
        }
        node->token->type = TokenType::STRING;
    }
    else 
    {
        std::cerr << "Error: you can't do this operation!\n";
        system("pause"); 
    }
}

void String::Functor::operator()(IsEqOperator& op)
{
    getVars();
    if(node->left->token->value == node->right->token->value)
    {
        node->token->value = "True";
    }
    else 
    {
        node->token->value = "False";
    }
    node->token->type = TokenType::BOOL;
}

void String::Functor::operator()(NotEqOperator& op)
{
    getVars();
    if(node->left->token->value != node->right->token->value)
    {
        node->token->value = "True";
    }
    else 
    {
        node->token->value = "False";
    }
    node->token->type = TokenType::BOOL;
}