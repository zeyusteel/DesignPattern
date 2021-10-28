//命令模式
/*
特点：将执行与任务分开，把任务作为一个个请求存放到任务列表统一管理
*/
#include <vector>
#include <iostream>

class CCommand 
{
public:
    virtual ~CCommand() = default;
    virtual void exec_command() = 0;
};

class CExector
{
public:
    void do_workA() { std::cout << "do a" << std::endl; }
    void do_workB() { std::cout << "do b" << std::endl; }
};

class CConcreteCommandA : public CCommand
{
public:
    explicit CConcreteCommandA(CExector *pExector) : m_pExector(pExector) {}
    virtual ~CConcreteCommandA() = default;
    virtual void exec_command() override {
        if (m_pExector) {
            m_pExector->do_workA();
        }
    }
private:
    CExector *m_pExector;
};


class CConcreteCommandB : public CCommand
{
public:
    explicit CConcreteCommandB(CExector *pExector) : m_pExector(pExector) {}
    virtual ~CConcreteCommandB() = default;
    virtual void exec_command() override {
        if (m_pExector) {
            m_pExector->do_workB();
        }
    }
private:
    CExector *m_pExector;
};

class CCommandControl
{
public:
    ~CCommandControl() { clear_command(); }
    void add_command(CCommand *pCommand) {
        if (pCommand) {
            m_commandVector.push_back(pCommand);
        }
    }

    void run_command() {
        for (auto &pCmd : m_commandVector) {
            pCmd->exec_command();
        }
    }

    void clear_command() {
        for (auto &pCmd : m_commandVector) {
            delete pCmd;
        }
        m_commandVector.clear();
    }

private:
    std::vector<CCommand *> m_commandVector;
};

int main(int argc, char const *argv[])
{
    CCommandControl control;
    CExector exector;

    control.add_command(new CConcreteCommandA(&exector));
    control.add_command(new CConcreteCommandB(&exector));
    control.run_command();

    return 0;
}
