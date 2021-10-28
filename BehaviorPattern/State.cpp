//状态模式
/*
特点：将特定状态相关的行为都存放到State状态中,context用于维护当前状态
*/

#include <iostream>

class CContext;
class CState
{
public:
    virtual ~CState() = default;
    virtual void handle_context(CContext *pContext) = 0;
    virtual void handle_work() = 0;
};

class CConcreteStateA : public CState
{
public:
    virtual ~CConcreteStateA() = default;
    virtual void handle_context(CContext *pContext) override;
    virtual void handle_work() override { std::cout << "State A work" << std::endl; }
};

class CConcreteStateB : public CState
{
public:
    virtual ~CConcreteStateB() = default;
    virtual void handle_context(CContext *pContext) override;
    virtual void handle_work() override { std::cout << "State B work" << std::endl; }
};


class CConcreteStateC : public CState
{
public:
    virtual ~CConcreteStateC() = default;
    virtual void handle_context(CContext *pContext) override;
    virtual void handle_work() override { std::cout << "State C work" << std::endl; }
};


class CContext
{
public:
    CContext() : m_pState(new CConcreteStateA()), m_iCondition(0) {} //默认状态
    ~CContext() { if (m_pState) { delete m_pState; } }

    inline void set_state(CState *pState) {//设置状态
        if (pState) {
            delete m_pState;
            m_pState = pState;
        }
    }

    void print_job() {//调用当前状态的任务
        m_pState->handle_work();
    }

    inline void set_cond(const int iCond) { //根据条件切换状态
        m_iCondition = iCond; 
        if (m_pState) {
            m_pState->handle_context(this);
        }
    };

    inline int get_cond() const { return m_iCondition; }

    CContext(const CContext&) = delete;
    CContext& operator=(const CContext&) = delete;

private:
    int m_iCondition;
    CState *m_pState;
};

void CConcreteStateA::handle_context(CContext *pContext) {
    if (pContext && pContext->get_cond() > 10) {
        pContext->set_state(new CConcreteStateB);
        std::cout << "set state b" << std::endl;
    }
}

void CConcreteStateB::handle_context(CContext *pContext) {
    if (pContext && pContext->get_cond() > 20 ) {
        pContext->set_state(new CConcreteStateC);
        std::cout << "set state c" << std::endl;
    }
}

void CConcreteStateC::handle_context(CContext *pContext) {
    if (pContext) {
        std::cout << "last state c" << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    CContext *pContext = new CContext();

    for (int i = 0; i < 25; i++) {
        pContext->set_cond(i);
        pContext->print_job();
    }
    

    delete pContext;
    return 0;
}

