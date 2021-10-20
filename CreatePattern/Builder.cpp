//建造者模式
/*
特点：组装复杂结构或者复杂流程 ,组装的方法抽象在builder,组装的过程存放在director
*/
#include <iostream>

//盖一个三层的建筑
class CBuilder{
public:
    virtual ~CBuilder() = default;
    virtual void build_groundFloor() = 0;
    virtual void build_secondFloor() = 0;
    virtual void build_thirdFloor() = 0;
    virtual int get_result() = 0;
};

//三层的办公楼
class COfficeBuilder : public CBuilder{
public:
    COfficeBuilder():m_iResult(0) {}
    virtual ~COfficeBuilder() = default;

    inline virtual void build_groundFloor() override {
        ++m_iResult;
    }

    inline virtual void build_secondFloor() override {
        ++m_iResult;
    }

    inline virtual void build_thirdFloor() override {
        ++m_iResult;
    }

    inline virtual int get_result() override {
        return m_iResult;
    }

private:
    int m_iResult;
};

class CDirector{
public:
    void construct_product(CBuilder *builder) {
        builder->build_groundFloor();
        builder->build_secondFloor();
        builder->build_thirdFloor();
    }
};

int main(int argc, char const *argv[])
{
    CBuilder *pBuilder = new COfficeBuilder();

    CDirector director;
    director.construct_product(pBuilder);
    std::cout << pBuilder->get_result() << std::endl;

    delete pBuilder;
    return 0;
}
