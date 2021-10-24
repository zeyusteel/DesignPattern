//访问者模式
/*
特点：以不同的身份访问不同的元素,可以在不改变元素类的情况下添加新的元素操作,适用于element结构相对稳定的系统，易于增加visitor
缺点：不易于增加element
双分派: element调用accept把visitor请进来, visitor再调用visit
*/
#include <iostream>
#include <string>

class CConcreteElementA;
class CConcreteElementB;
class CVisitor
{
public:
    virtual ~CVisitor() = default;
    virtual void visit_element(CConcreteElementA *) = 0;
    virtual void visit_element(CConcreteElementB *) = 0;
};

class CElement 
{
public:
    virtual ~CElement() = default;
    virtual void accept(CVisitor *) = 0;
};

class CConcreteElementA : public CElement 
{
public:
    CConcreteElementA() : m_iFlag(5) {}
    virtual ~CConcreteElementA() = default;
public:
    inline virtual void accept(CVisitor *pVisitor) override {
        pVisitor->visit_element(this);
    }

    inline int get_flag() const { return m_iFlag; }

private:
    int m_iFlag;
};

class CConcreteElementB : public CElement 
{
public:
    CConcreteElementB() : m_str("test") {}
    virtual ~CConcreteElementB() = default;
public:
    inline virtual void accept(CVisitor *pVisitor) override {
        pVisitor->visit_element(this);
    }

    inline std::string get_str() const { return m_str; }

private:
    std::string m_str;
};

class CConcreteVisitorA : public CVisitor 
{
public:
    virtual ~CConcreteVisitorA() = default;
    inline virtual void visit_element(CConcreteElementA *pA) override {
        std::cout << pA->get_flag() << "CConcreteVisitorA" << std::endl;
    }
    inline virtual void visit_element(CConcreteElementB *pB) override {
        std::cout << pB->get_str() << "CConcreteVisitorA" << std::endl;
    }
};

class CConcreteVisitorB : public CVisitor 
{
public:
    virtual ~CConcreteVisitorB() = default;
    inline virtual void visit_element(CConcreteElementA *pA) override {
        std::cout <<pA->get_flag() << "CConcreteVisitorB" << std::endl;
    }
    inline virtual void visit_element(CConcreteElementB *pB) override {
        std::cout <<pB->get_str() << "CConcreteVisitorB" << std::endl;
    }

};

int main(int argc, char const *argv[])
{
    CConcreteVisitorA *pVisitorA = new CConcreteVisitorA();
    CConcreteVisitorB *pVisitorB = new CConcreteVisitorB();

    CConcreteElementA *pElementA = new CConcreteElementA();
    pElementA->accept(pVisitorA);
    pElementA->accept(pVisitorB);

    delete pElementA;
    delete pVisitorA;
    delete pVisitorB;
    return 0;
}
