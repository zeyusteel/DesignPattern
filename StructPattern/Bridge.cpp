//桥接模式
/*
特点：如果实现可以有多种角度分类，为了让每一种分类都可以动态变化,就要把这种角度分离出来让它独立变化,减少耦合 
用has a 而不是 is a
*/

#include <iostream>

//被分离出来的实现
class CImplementor
{
public:
    virtual ~CImplementor() = default;
    virtual void do_work() = 0;
};

class CConcreteImplementorA : public CImplementor
{
public:
    virtual ~CConcreteImplementorA() = default;
    virtual void do_work() override {
        std::cout << "CConcreteImplementorA" << std::endl;               
    }
};

class CConcreteImplementorB : public CImplementor
{
public:
    virtual ~CConcreteImplementorB() = default;
    virtual void do_work() override {
        std::cout << "CConcreteImplementorB" << std::endl;               
    }
};

class CAbstraction
{
public:
    CAbstraction() : m_Implementor(nullptr) {}
    virtual ~CAbstraction() { 
        if (m_Implementor) { 
            delete m_Implementor; 
        } 
    }

    void set_implementor(CImplementor *pImplementor) {
        if (pImplementor) {
            m_Implementor = pImplementor;
        }
    }

    virtual void do_work() {
        m_Implementor->do_work();
    }

    CAbstraction(const CAbstraction&) = delete;
    CAbstraction& operator=(const CAbstraction&) = delete;

private:
    CImplementor *m_Implementor;
};

class CRefineAbstractionA: public CAbstraction
{
public:
    virtual ~CRefineAbstractionA() = default;
    virtual void do_work() override {
        CAbstraction::do_work();
        std::cout << "CRefineAbstractionA" << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    CAbstraction *pAbstraction = new CRefineAbstractionA();

    pAbstraction->set_implementor(new CConcreteImplementorA());
    pAbstraction->do_work();

    delete pAbstraction;
    return 0;
}
