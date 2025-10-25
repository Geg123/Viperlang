#include"Objects.h"

class ObjectManager
{
public:
    static void InsertObject(Object obj);
    static Object getObject(std::string name);
    static void getValue(std::shared_ptr<NodeAST> node);
    static void run_func(std::shared_ptr<NodeAST> node, std::shared_ptr<Function> funcptr);
private:
    ObjectManager();
    static std::unordered_map<std::string, Object> objects;
};