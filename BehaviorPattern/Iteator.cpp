//迭代器模式
/*
特点：通过迭代器访问聚集对象，又不暴露出聚集对象内部结构
*/
#include <vector>
#include <iostream>

class CCore;
using CORE_VECTOR = std::vector<CCore*>;
using CORE_ITOR = std::vector<CCore*> :: iterator;

class CCore
{
public:
    virtual ~CCore(){
        std::cout << "delete base core" << std::endl;
    }
    virtual void run_core() = 0;
};

class CHwCore : public CCore
{
public:
    virtual ~CHwCore() {
        std::cout << "delete hw core" << std::endl;
    }
    inline virtual void run_core() override {
        std::cout << "run hw core" << std::endl;
    }
};

class CHpCore : public CCore
{
public:
    virtual ~CHpCore() {
        std::cout << "delete hp core" << std::endl;
    }
    inline virtual void run_core() override {
        std::cout << "run hp core" << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    CORE_VECTOR coreVec;

    coreVec.push_back(new CHwCore());
    coreVec.push_back(new CHpCore());

    CORE_ITOR itor = coreVec.begin();
    for (; itor != coreVec.end(); ++itor) {
        CCore *pCore = *itor;
        pCore->run_core();
    }

    for (auto &p : coreVec) {
        delete p;
    }
    
    return 0;
}
