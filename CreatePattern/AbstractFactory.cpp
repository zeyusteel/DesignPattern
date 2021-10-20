//抽象工厂
/*
特点：提供一系列相关或相互依赖对象的创建接口,如果客户端产品需要全套替换时,只需要改工厂初始化为其他类别.具体的实例化过程与客户端分离，客户端只操作抽象接口
缺点：添加一种新产品需要为每一种工厂添加、工厂数量多代码维护不方便、每一种工厂无法与客户端解耦,如果要替换其他工厂的话需要将所有构造工厂的地方替换
类似于华为工厂生产：华为cpu、华为内存... 联想工厂生产：联想cpu,联想内存... ,抽象工厂按不同类别工厂去抽象，工厂方法类按不同类别产品抽象
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

/*********************** 加法器 ********************/
class COperationAdd : public COperation
{
public:
    explicit COperationAdd(double iNumA = 0, double iNumB = 0) : COperation(iNumA, iNumB) {}
    virtual ~COperationAdd() = default;

public:
    virtual double get_result() const = 0;
};

//A算法的加法器
class CAMethodOperationAdd : public COperationAdd
{
public:
    explicit CAMethodOperationAdd(double iNumA = 0, double iNumB = 0) : COperationAdd(iNumA, iNumB) {}
    virtual ~CAMethodOperationAdd() = default;

public:
    inline virtual double get_result() const override {
        std::cout << "A Method" << std::endl;
        return get_numA() + get_numB();
    }

};

//B算法的加法器
class CBMethodOperationAdd : public COperationAdd
{
public:
    explicit CBMethodOperationAdd(double iNumA = 0, double iNumB = 0) : COperationAdd(iNumA, iNumB) {}
    virtual ~CBMethodOperationAdd() = default;

public:
    inline virtual double get_result() const override {
        std::cout << "B Method" << std::endl;
        return get_numA() + get_numB();
    }

};

/*********************** 减法器 ********************/
class COperationSub : public COperation
{
public:
    explicit COperationSub(double iNumA = 0, double iNumB = 0) : COperation(iNumA, iNumB) {}
    virtual ~COperationSub() = default;

public:
    virtual double get_result() const = 0;
};

//A算法的减法器
class CAMethodOperationSub : public COperationSub
{
public:
    explicit CAMethodOperationSub(double iNumA = 0, double iNumB = 0) : COperationSub(iNumA, iNumB) {}
    virtual ~CAMethodOperationSub() = default;

public:
    inline virtual double get_result() const override {
        std::cout << "A Method" << std::endl;
        return get_numA() - get_numB();
    }

};

//B算法的减法器
class CBMethodOperationSub : public COperationSub
{
public:
    explicit CBMethodOperationSub(double iNumA = 0, double iNumB = 0) : COperationSub(iNumA, iNumB) {}
    virtual ~CBMethodOperationSub() = default;

public:
    inline virtual double get_result() const override {
        std::cout << "B Method" << std::endl;
        return get_numA() - get_numB();
    }

};

class CAbstractFactory
{
public:
    CAbstractFactory() = default;
    virtual ~CAbstractFactory() = default;

public:
    virtual COperation* creat_operationAdd() const = 0;
    virtual COperation* creat_operationSub() const = 0;
};

class CAMethodFactory : public CAbstractFactory{
public:
    CAMethodFactory() = default;
    virtual ~CAMethodFactory() = default;

public:
    inline virtual COperation* creat_operationAdd() const {
        return new CAMethodOperationAdd();
    }

    inline virtual COperation* creat_operationSub() const {
        return new CAMethodOperationSub();
    }

};

class CBMethodFactory : public CAbstractFactory{
public:
    CBMethodFactory() = default;
    virtual ~CBMethodFactory() = default;

public:
    inline virtual COperation* creat_operationAdd() const {
        return new CBMethodOperationAdd();
    }

    inline virtual COperation* creat_operationSub() const {
        return new CBMethodOperationSub();
    }

};

int main(int argc, char const *argv[])
{
    CAbstractFactory *pFactory = new CAMethodFactory();
    COperation *pOpr = pFactory->creat_operationAdd();

    pOpr->set_numA(3);
    pOpr->set_numA(7);
    std::cout << pOpr->get_result() << std::endl;

    delete pOpr;
    delete pFactory;
    return 0;
}
