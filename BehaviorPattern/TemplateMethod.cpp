//模版方法模式
/*
    在父类定义模版方法的框架，将框架内的步骤延迟到各自子类实现
*/
#include <iostream>

class CAbstract
{
public:
    virtual ~CAbstract() = default;
    inline void run_templateMethod() const {
        run_stepOne();
        run_stepTwo();
    }

protected:
    virtual void run_stepOne() const = 0;
    virtual void run_stepTwo() const = 0;
};

class ConcreteA : public CAbstract
{
public:
    virtual ~ConcreteA() = default;

private:
    inline virtual void run_stepOne() const override {
        std::cout << "hello" ;
    }

    inline virtual void run_stepTwo() const override {
        std::cout << "world" << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    CAbstract *pObj = new ConcreteA();
    pObj->run_templateMethod();
    delete pObj; 
    return 0;
}
