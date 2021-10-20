//工厂方法类:
/*
特点：定义创建对象的接口，让工厂的子类决定实例化哪一个产品类,工厂方法使一个产品类的实例化延迟到工厂的子类,代码可扩展性增加,将简单工厂判断的过程迁移到了客户端
缺点：每一个产品都对应一个工厂，代码量增大
*/

#include <iostream>

class COperation
{
public:
    explicit COperation(double iNumA = 0, double iNumB = 0) : m_iNumA(iNumA), m_iNumB(iNumB) {}
    virtual ~COperation() = default;

public:
    inline double get_numA() const { return m_iNumA; }
    inline double get_numB() const { return m_iNumB; }
    inline void set_numB(double iNum) { m_iNumB = iNum; }
    inline void set_numA(double iNum) { m_iNumA = iNum; }

public:
    virtual double get_result() const = 0;

private:
    double m_iNumA;
    double m_iNumB;
};

class COperationAdd : public COperation
{
public:
    explicit COperationAdd(double iNumA = 0, double iNumB = 0) : COperation(iNumA, iNumB) {}
    virtual ~COperationAdd() = default;

public:
    inline virtual double get_result() const override {
        return get_numA() + get_numB();
    }
};

class COperationSub : public COperation
{
public:
    explicit COperationSub(double iNumA = 0, double iNumB = 0) : COperation(iNumA, iNumB) {}
    virtual ~COperationSub() = default;

public:
    inline virtual double get_result() const override {
        return get_numA() - get_numB();
    }
};

class FactoryMethod
{
public:
    FactoryMethod() = default;
    virtual ~FactoryMethod() = default;

public:
    virtual COperation* creat_operation() const = 0;
};

class AddFactoryMethod : public FactoryMethod
{
    inline virtual COperation* creat_operation() const override {
        return new COperationAdd();
    }
};

class SubFactoryMethod : public FactoryMethod
{
    inline virtual COperation* creat_operation() const override {
        return new COperationSub();
    }
};

int main(int argc, char const *argv[])
{
    FactoryMethod *pFactory = new AddFactoryMethod();
    COperation *pOpr = pFactory->creat_operation();

    pOpr->set_numA(2);
    pOpr->set_numB(2);
    std::cout << pOpr->get_result() << std::endl;

    delete pOpr;
    delete pFactory;

    return 0;
}
