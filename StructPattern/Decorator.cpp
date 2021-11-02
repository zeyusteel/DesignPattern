//装饰模式
/*
特点：动态的给一些对象添加额外功能
*/
#include <iostream>

class CComponent
{
public:
    virtual ~CComponent() = default;
    virtual void do_work() = 0;
};

class CConcreteComponent : public CComponent
{
public:
    virtual ~CConcreteComponent() = default;
    virtual void do_work() override {
        std::cout << "CConcreteComponent do work" << std::endl;
    }
};

class CDecorator : public CComponent
{
public:
    CDecorator() : m_pComponent(nullptr) {}
    virtual ~CDecorator() = default;
    void set_component(CComponent *pComponent) { m_pComponent = pComponent; }
    virtual void do_work() override {
        if (m_pComponent) {
            m_pComponent->do_work();
        }
    }
    bool check_component() const { return m_pComponent; }

private:
    CComponent *m_pComponent;
};

class CConcreteDecoratorA : public CDecorator
{
public:
    virtual ~CConcreteDecoratorA() = default;
    virtual void do_work() override {
        if (check_component()) {
            CDecorator::do_work();
            do_moreWork();
        }
    }

private:
    void do_moreWork() { std::cout << "CConcreteDecoratorA do more work" << std::endl; }
};

class CConcreteDecoratorB : public CDecorator
{
public:
    virtual ~CConcreteDecoratorB() = default;
    virtual void do_work() override {
        if (check_component()) {
            CDecorator::do_work();
            do_moreWork();
        }
    }

private:
    void do_moreWork() { std::cout << "CConcreteDecoratorB do more work" << std::endl; }
};

int main(int argc, char const *argv[])
{
    CComponent *pComponent = new CConcreteComponent();
    CConcreteDecoratorA *pA = new CConcreteDecoratorA();
    CConcreteDecoratorB *pB = new CConcreteDecoratorB();

    pA->set_component(pComponent);
    pB->set_component(pA);
    pB->do_work();

    delete pComponent;
    delete pA;
    delete pB;
    return 0;
}

