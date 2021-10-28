//解释器模式
/*
定义语言的文法，用解释器去解释
*/
#include <string>
#include <iostream>
#include <vector>

class CContext
{
public:
    explicit CContext(const std::string &str) : m_str(str) {}
    std::string get_string() { return m_str; }
    void set_string(const std::string &str) { m_str = str; }
private:
    std::string m_str;
};

class CExpression
{
public:
    virtual ~CExpression() = default;
    virtual void interprete(CContext*) = 0;
};

class CTerminalExpression : public CExpression
{
public:
    virtual ~CTerminalExpression() = default;
    inline virtual void interprete(CContext *pContext) override {
        std::cout << pContext->get_string() << std::endl;
        std::string strTmp = pContext->get_string();
        strTmp.pop_back();
        pContext->set_string(strTmp);
    }
};

class CNonterminalExpression : public CExpression
{
public:
    virtual ~CNonterminalExpression() = default;
    inline virtual void interprete(CContext *pContext) override {
        std::cout << pContext->get_string() << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    std::vector<CExpression*> vector; 
    CContext *pContext = new CContext("abcd");
    vector.push_back(new CTerminalExpression());
    vector.push_back(new CTerminalExpression());
    vector.push_back(new CNonterminalExpression());

    for (auto &expression : vector) {
        expression->interprete(pContext);
    }

    for (auto &expression : vector) {
        delete expression;
    }

    delete pContext;
    return 0;
}
