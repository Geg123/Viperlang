#include"../include/Operators.h"

std::unordered_set<TokenType> operators{ TokenType::PLUS, TokenType::MINUS, TokenType::MULT, TokenType::DIV, TokenType::MODULE, TokenType::AND, TokenType::OR, TokenType::IS_EQ, TokenType::NOT, TokenType::NOT_EQ };

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
    else if(left == TokenType::BOOL || right == TokenType::BOOL)
	    return new Bool;
    else if (left == TokenType::FALSE || right == TokenType::FALSE)
        return new Bool;
    else if (left == TokenType::TRUE || right == TokenType::TRUE)
        return new Bool;
}

Type* BasicVarTypeToType(BasicVarType type)
{ 
	if(type == BasicVarType::INT)
        return new Int;
    else if(type == BasicVarType::STRING)
	    return new String;
    else if(type == BasicVarType::BOOL)
	    return new Bool;
}

void OperatorsManager::InsertObject(std::shared_ptr<Object> obj)
{
    objects->insert({obj->name, obj});
}

Type* OperatorsManager::TokenTypeToType(std::shared_ptr<NodeAST> node)
{
    TokenType left = TokenType::BOOL;
    TokenType right = TokenType::BOOL;
    BasicVarType var_type;
    if(node->left == nullptr && node->right == nullptr)
    {
        if(node->token->type == TokenType::VAR)
        {
            return BasicVarTypeToType(dynamic_cast<Variable*>(objects->at(node->token->value).get())->type);
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
    else if(left == TokenType::VAR)
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
            if(int(tmp_var_type) > int(var_type))
            {
                var_type = tmp_var_type;
            }
            return BasicVarTypeToType(var_type);
        }
        else 
        {
            std::cerr << "Error: var " << tmp_var_name << " doesn't exist!\n";
            system("pause");
        }
    }
    else if(right == TokenType::VAR)
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
            if(int(tmp_var_type) > int(var_type))
            {
                var_type = tmp_var_type;
            }
            return BasicVarTypeToType(var_type);
        }
        else 
        {
            std::cerr << "Error: var " << tmp_var_name << " doesn't exist!\n";
            system("pause");
        }
    }
    else 
    {
        return TokenTypeToTypeSwitcher(left , right);
    }
}

void OperatorsManager::DoOperation(std::shared_ptr<NodeAST> node)
{
    Type* type = TokenTypeToType(node);
    if(!type->test())
    {
        DoOperation(node->left);
        DoOperation(node->right);
    }
    TypeOperations op = NodeTypeToOperator(node);
    type->executeOperation(node, op, objects);
    delete type;
}

void Bool::executeOperation(std::shared_ptr<NodeAST> node, TypeOperations op, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> _objects)
{
    std::visit(Functor(node, _objects), op);
}

TypeOperations OperatorsManager::NodeTypeToOperator(std::shared_ptr<NodeAST> node)
{
    TypeOperations a;
    int type = int(node->token->type);
    switch (type)
    {
    //case 1: return a = EqOperator{};
    //case 2: return a = PlusOperator{};
    //case 3: return a = MinusOperator{};
    //case 11: return a = NotOperator{};
    case 12: return a = IsEqOperator{};
    case 13: return a = NotEqOperator{};
    //case 17: return a = MultOperator{};
    //case 18: return a = DivOperator{};
    //case 28: return a = GreaterOperator{};
    //case 29: return a = LessOperator{};
    case 30: return a = AndOperator{};
    case 31: return a = OrOperator{};
    }
    return EqOperator{};
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