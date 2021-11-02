//轻量模式
/*
特点:对象共享,减少构造
*/
#include <iostream>
#include <map>

class CFlyWeight
{
public:
    virtual ~CFlyWeight() = default;
    virtual void do_work() = 0;
};

class CConcreteFlyWeightA : public CFlyWeight
{
public:
    virtual ~CConcreteFlyWeightA() = default;
    virtual void do_work() override {
        std::cout << "CConcreteFlyWeightA do work" << std::endl;        
    }
};

class CFlyWeightFactory
{
public:
    ~CFlyWeightFactory() {
        for (auto pair : m_map) {
            delete pair.second;
        }
        m_map.clear();
    }

    CFlyWeightFactory(const CFlyWeightFactory &) = delete;
    CFlyWeightFactory(CFlyWeightFactory &&) = delete;
    CFlyWeightFactory& operator=(const CFlyWeightFactory &) = delete;
    CFlyWeightFactory& operator=(CFlyWeightFactory &&) = delete;

public:
    static CFlyWeightFactory& get_instance() {
        static CFlyWeightFactory factory;
        return factory;
    } 

    CFlyWeight* get_flyWeight(const int iKey) {
        auto itor = m_map.find(iKey);

        if (itor != m_map.end()) {
            return itor->second;
        } else {
            CFlyWeight *pFlyWeight = nullptr;
            pFlyWeight = new CConcreteFlyWeightA();
            m_map.insert(std::make_pair(iKey, pFlyWeight));
            return pFlyWeight;
        }
    }

protected:
    CFlyWeightFactory() = default;

private:
    std::map<int, CFlyWeight*> m_map;
};

int main(int argc, char const *argv[])
{
    CFlyWeight *pObj = CFlyWeightFactory::get_instance().get_flyWeight(1);
    pObj->do_work();
    return 0;
}