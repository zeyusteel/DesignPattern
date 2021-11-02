//适配器模式
/*
特点:想使用一个已经存在的类，但是类的接口与需要的不同又不好修改这个类时,采用适配器模式
*/
#include <iostream>

//我们希望的接口
class CNeedObj
{
public:
    virtual ~CNeedObj() = default;
    virtual void need_func() = 0;
};

class CConcreteNeedObj : public CNeedObj
{
public:
    virtual ~CConcreteNeedObj() = default;
    virtual void need_func() override {
        std::cout << "need func" << std::endl;
    }
};

//能实现需要的功能,但是接口不同
class COtherObj
{
public:
    void need_funcByOther() {
        std::cout << "ohter func" << std::endl;
    }
};

//适配器
class CAdapter : public CNeedObj
{
public:
    virtual void need_func() override {
        m_obj.need_funcByOther();
    }

private:
    COtherObj m_obj;
};

int main(int argc, char const *argv[])
{
    CNeedObj *pObj = new CConcreteNeedObj(); 
    pObj->need_func();

    CNeedObj *pOtherObj = new CAdapter();
    pOtherObj->need_func();

    delete pOtherObj;
    delete pObj;

    return 0;
}
