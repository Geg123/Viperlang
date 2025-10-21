#include"Objects.h"

class ObjectManager
{
public:
    static void InsertObject(Object obj);
    static Object getObject(std::string name);
private:
    ObjectManager();
    static std::unordered_map<std::string, Object> objects;
};

std::shared_ptr<NodeAST> run_func(size_t iter, size_t end_iter, std::shared_ptr<Function> function);