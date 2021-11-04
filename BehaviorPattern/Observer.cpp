//观察者模式
/*
特点:多个观察者监听同一主题对象，主题改变时通知所有观察者
*/

#include <vector>
#include <iostream>

class CObject;
class CObserver
{
public:
    virtual ~CObserver() = default;
    virtual void update_cond(CObject *) = 0;
};

class CObject 
{
public:
    virtual ~CObject() = default;

public:
    void add_observer(CObserver *pObserver) {
        m_vector.push_back(pObserver);
    }

    void del_observer(CObserver *pObserver) {
        m_vector.erase(std::remove(m_vector.begin(), m_vector.end(), pObserver), m_vector.end());
    }

    void notify_observers() {
        for (auto observer : m_vector) {
            observer->update_cond(this);
        }
    }       

    virtual void do_work() = 0;
    virtual int get_cond() const = 0;

private:
    std::vector<CObserver *> m_vector;
};

class CConcreteObjectA : public CObject
{
public:
    CConcreteObjectA() : m_iCond(0) {}
    virtual ~CConcreteObjectA() = default;

public:
    virtual void do_work() override {
        std::cout << "CConcreteObjectA do work" << std::endl;
        m_iCond = 99;
        notify_observers();
    }
    
    virtual int get_cond() const override { return m_iCond; }

private:
    int m_iCond;

};

class CConcreteObserverA : public CObserver
{
public:
    virtual ~CConcreteObserverA() = default;
    virtual void update_cond(CObject *pObj) override {
        std::cout << pObj->get_cond() << std::endl;
    }
};

class CConcreteObserverB : public CObserver
{
public:
    virtual ~CConcreteObserverB() = default;
    virtual void update_cond(CObject *pObj) override {
        std::cout << pObj->get_cond() << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    CObject *pObj = new CConcreteObjectA();    
    CObserver *pObserverA = new CConcreteObserverA(); 
    CObserver *pObserverB = new CConcreteObserverB(); 

    pObj->add_observer(pObserverA);
    pObj->add_observer(pObserverB);
    pObj->do_work();

    delete pObj;
    delete pObserverA;
    delete pObserverB;
    return 0;
}
