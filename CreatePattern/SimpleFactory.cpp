//简单工厂
/*
特点：工厂中包含了必要的判断逻辑，根据客户端的选择动态实例化相关的类，去除了客户端与具体产品的依赖
缺点：如果需要给工厂新添产品，需要破坏原有类添加case分支，违背开放封闭原则
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


class CSimpleFactory
{
public:
    inline COperation* creat_operation(char cOperate) const 
    {
        COperation *pOper = nullptr;

        switch (cOperate)
        {
        case '+':
            pOper = new COperationAdd();
            break;
        case '-':
            pOper = new COperationSub();
            break;
        default:
            break;
        }

        return pOper;
    }
};


int main(int argc, char const *argv[])
{
    CSimpleFactory factory;    
    COperation *pOperation = factory.creat_operation('-');
    pOperation->set_numA(3.1);
    pOperation->set_numB(5);

    std::cout << pOperation->get_result() << std::endl;
    delete pOperation;

    return 0;
}
