//组合模式
/*
特点：树型结构表示 部分-整体 的结构层次, 单个对象与组合对象具有一致性的接口,用户不用做区分
*/
#include <iostream>
#include <string>
#include <vector>

class CComponent
{
public:
    virtual ~CComponent() = default;
    virtual void add_component(CComponent *) {}
    virtual void show_name() = 0;
};

class CLeaf : public CComponent
{
public:
    explicit CLeaf(const std::string &strName) : m_strName(strName) {}
    virtual ~CLeaf() = default;

public:
    virtual void show_name() override {
        std::cout << m_strName << std::endl;
    }

private:
    std::string m_strName;
};

class CComposite : public CComponent
{
public:
    explicit CComposite(const std::string &strName) : m_strName(strName) {}
    virtual ~CComposite() = default;

public:
    virtual void add_component(CComponent *pComponent) override {
        if (pComponent) {
            m_vec.push_back(pComponent);
        }
    }

    virtual void show_name() override {
        std::cout << m_strName << std::endl;

        for (auto component : m_vec) {
            component->show_name();
        }
    }

private:
    std::string m_strName;
    std::vector<CComponent*> m_vec;     
};

int main(int argc, char const *argv[])
{
    CComponent *pRoot = new CComposite("/root/");
    CComponent *pBin = new CComposite("/bin/");
    CComponent *pLib = new CComposite("/lib/");

    CComponent *pTestBin = new CLeaf("test");
    CComponent *pTestLib= new CLeaf("test.so");

    pBin->add_component(pTestBin);
    pLib->add_component(pTestLib);

    pRoot->add_component(pBin);
    pRoot->add_component(pLib);

    pRoot->show_name();

    delete pLib;
    delete pRoot;
    delete pBin;
    delete pTestBin;
    delete pTestLib;

    return 0;
}
