//策略模式
/*
特点：策略模式用来封装算法,这些算法都是实现相同的工作，只是实现不同。可以通过相同的调用方式调用不同的算法，减少算法之间的耦合
*/
#include <iostream>

class CStrategy
{
public:
    CStrategy() = default;
    virtual ~CStrategy() = default;

    virtual void encrypt_asymm() = 0;
    virtual void decrypt_asymm() = 0;
};

class CConcreteStrategyA : public CStrategy
{
public:
    CConcreteStrategyA() = default;
    virtual ~CConcreteStrategyA() = default;

    inline virtual void encrypt_asymm() override {
        std::cout << "concrete A encrypt_asymm" << std::endl;
    }

    inline virtual void decrypt_asymm() override {
        std::cout << "concrete A decrypt_asymm" << std::endl;
    }
};

class CConcreteStrategyB : public CStrategy
{
public:
    CConcreteStrategyB() = default;
    virtual ~CConcreteStrategyB() = default;

    inline virtual void encrypt_asymm() override {
        std::cout << "concrete B encrypt_asymm" << std::endl;
    }

    inline virtual void decrypt_asymm() override {
        std::cout << "concrete B decrypt_asymm" << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    CStrategy *pObj = new CConcreteStrategyA();

    pObj->encrypt_asymm();
    pObj->decrypt_asymm();

    delete pObj;
    return 0;
}



