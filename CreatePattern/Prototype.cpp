//原型模式
/*
特点：通过拷贝原型创建对象 new时也可以使用
*/
#include <string>
#include <iostream>

class CObject
{
public:
    CObject() = default;
    virtual ~CObject() = default;
    virtual CObject* clone_obj() const = 0;
    virtual void show_str() const = 0;
    virtual void set_str(const std::string &) = 0;
};

class CTestObject : public CObject
{
public:
    explicit CTestObject(const std::string &m_str) : m_strShow(m_str){}
    virtual ~CTestObject() = default;

    CTestObject(const CTestObject &obj) : m_strShow(obj.m_strShow) {}
    inline CTestObject& operator=(const CTestObject &obj) {
        m_strShow = obj.m_strShow;
        return *this;
    }

    CTestObject(CTestObject &&obj):m_strShow(std::move(obj.m_strShow)) {} 
    inline CTestObject& operator=(CTestObject &&obj) {
        m_strShow = std::move(obj.m_strShow);
        return *this;
    }

public:
    inline virtual CObject* clone_obj() const override {
        return new CTestObject(m_strShow);
    }

    inline virtual void show_str() const override {
        std::cout << m_strShow << std::endl; 
    }

    inline virtual void set_str(const std::string &str) override {
        m_strShow = str;
    }


private:
    std::string m_strShow;
};

int main(int argc, char const *argv[])
{
    CTestObject *pObj = new CTestObject("hhhhhh");
    auto pCloneObj = pObj->clone_obj();

    pObj->show_str();
    pCloneObj->show_str();
    
    pObj->set_str("ttt");

    pObj->show_str();
    pCloneObj->show_str();

    delete pObj;
    delete pCloneObj;

    return 0;
}
