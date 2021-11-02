//代理模式
/*
特点：为一个对象提供代理，通过代理实现对这个对象的操作
*/
#include <iostream>

class CObject
{
public:
    virtual ~CObject() = default;
    virtual void do_work() = 0;
};

class CConcreteObjectA : public CObject
{
public:
    virtual ~CConcreteObjectA() = default;
    virtual void do_work() override {
        std::cout << "CConcreteObjectA" << std::endl; 
    }
};

class CProxy : public CObject
{
public:
    CProxy() : m_pObj(nullptr) {}
    virtual ~CProxy() {
        if (m_pObj) {
            delete m_pObj;
            m_pObj = nullptr;
        }
    } 
    virtual void do_work() override {
        if (!m_pObj) {
            m_pObj = new CConcreteObjectA();
        }
        m_pObj->do_work();
    }

private:
    CConcreteObjectA *m_pObj;
};

int main(int argc, char const *argv[])
{
    CProxy *pProxy = new CProxy();
    pProxy->do_work();
    delete pProxy;
    return 0;
}
