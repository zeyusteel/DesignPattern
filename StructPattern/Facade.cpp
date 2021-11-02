//外观模式
/*
特点：为系统中的一组复杂接口提供一致的对外界面
*/
#include <iostream>

class CSubSystem
{
public:
    virtual ~CSubSystem() = default;
    virtual void do_work() = 0;
};

class CConcreteSubSystemA : public CSubSystem
{
public:
    virtual ~CConcreteSubSystemA() = default;
    virtual void do_work() override {
        std::cout << "CConcreteSubSystemA do sub work" << std::endl;
    }
};

class CConcreteSubSystemB : public CSubSystem
{
public:
    virtual ~CConcreteSubSystemB() = default;
    virtual void do_work() override {
        std::cout << "CConcreteSubSystemB do sub work" << std::endl;
    }
    void do_otherWork() {
        std::cout << "do other sub work" << std::endl;
    }
};

class CFacade
{
public:
    static CFacade& get_instance() {
        static CFacade facade;
        return facade;
    }

    ~CFacade() {
        if (m_pObjA) { delete m_pObjA; }
        if (m_pObjB) { delete m_pObjB; }
    }

    CFacade(const CFacade &) = delete;
    CFacade(CFacade &&) = delete;
    CFacade& operator=(const CFacade &) = delete;
    CFacade& operator=(CFacade &&) = delete;

    void do_workMethodA() {
        m_pObjA->do_work();
        m_pObjB->do_otherWork();
    }

    void do_workMethodB() {
        m_pObjB->do_work();
        m_pObjB->do_otherWork();
        m_pObjA->do_work();
    }

protected:
    CFacade() : m_pObjA(nullptr), m_pObjB(nullptr) {
        m_pObjA = new CConcreteSubSystemA();
        m_pObjB = new CConcreteSubSystemB();
    }

private:
    CConcreteSubSystemA *m_pObjA;
    CConcreteSubSystemB *m_pObjB;
};

int main(int argc, char const *argv[])
{
    CFacade::get_instance().do_workMethodA();
    CFacade::get_instance().do_workMethodB();
    return 0;
}
