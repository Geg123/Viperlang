#include"Objects.h"

class ObjectManager
{
public:
    static ObjectManager* getInstance();
    void InsertObject(std::shared_ptr<Object> obj);
    std::shared_ptr<Object> getObject(std::string name);
private:
    static ObjectManager* manager;
    ObjectManager();
    std::unordered_map<std::string, std::shared_ptr<Object>> objects;
};

std::shared_ptr<NodeAST> run_func(size_t iter, size_t end_iter, std::shared_ptr<Function> function);