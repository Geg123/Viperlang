#include"Objects.h"

class ObjectManager
{
public:
    static void InsertObject(Object obj);
    static Object getObject(std::string name);
    static void getValue(std::shared_ptr<NodeAST> node);
    static void run_func(std::shared_ptr<NodeAST> node, std::shared_ptr<Function> funcptr);
    static void setScope(std::string name);
    static void start()
    {
        func_iter = 0;
        setScope("global");
    }
    static void incrementIter(){++func_iter;}
    static void decrementIter(){--func_iter;}
    static void CalcExpr(std::shared_ptr<NodeAST> node);
private:
    ObjectManager();
    static size_t func_iter;
    static std::unordered_map<std::string, Object>* objects;
    static std::unordered_map<std::string, Object> global;
    static std::unordered_map<std::string, std::unordered_map<std::string, Object>> scopes;
};

NodeAST copyNodeTo(std::shared_ptr<NodeAST> node);