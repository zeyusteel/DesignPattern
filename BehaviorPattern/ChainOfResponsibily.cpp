//责任链模式
/*
特点：将责任踢给后继节点
*/
#include <iostream>

class CRequest
{
public:
    explicit CRequest(int iLevel) : m_iRequestLevel(iLevel) {}
    inline int get_level() const { return m_iRequestLevel; }

private:
    int m_iRequestLevel;
};

class CHandler
{
public:
    CHandler() : m_pNextHandler(nullptr) {}
    virtual ~CHandler() = default;

public:
    inline CHandler* set_nextHandler(CHandler *pHandler) {
        m_pNextHandler = pHandler;
        return pHandler;
    }

    void handle_request(CRequest *pRequest) {
        if (pRequest && (try_handleRequest(pRequest))) {
            std::cout << "handle success" << std::endl;
        } else if (m_pNextHandler) {
            std::cout << "throw to next handler" << std::endl;
            m_pNextHandler->handle_request(pRequest);
        } else {
            std::cout << "can not be handle" << std::endl;
        }
    }

protected:
    virtual bool try_handleRequest(CRequest *) const = 0;

private:
    CHandler *m_pNextHandler;
};

class CConcreteHandlerA : public CHandler
{
public:
    virtual ~CConcreteHandlerA() = default;
    inline virtual bool try_handleRequest(CRequest *pRequest) const override {
        if (pRequest && pRequest->get_level() < 5) {
            return true;
        }
        return false;
    }

};

class CConcreteHandlerB : public CHandler
{
public:
    virtual ~CConcreteHandlerB() = default;
    inline virtual bool try_handleRequest(CRequest *pRequest) const override {
        if (pRequest && pRequest->get_level() >= 5 && pRequest->get_level() < 10) {
            return true;
        }
        return false;
    }

};

class CConcreteHandlerC : public CHandler
{
public:
    virtual ~CConcreteHandlerC() = default;
    inline virtual bool try_handleRequest(CRequest *pRequest) const override {
        if (pRequest && pRequest->get_level() >= 10 && pRequest->get_level() < 15) {
            return true;
        }
        return false;
    }
};

int main(int argc, char const *argv[])
{
    CConcreteHandlerA *pHandlerA = new CConcreteHandlerA();
    CConcreteHandlerB *pHandlerB = new CConcreteHandlerB();
    CConcreteHandlerC *pHandlerC = new CConcreteHandlerC();

    CRequest *pRequest = new CRequest(10);

    pHandlerA->set_nextHandler(pHandlerB)->set_nextHandler(pHandlerC);
    pHandlerA->handle_request(pRequest);

    delete pRequest;
    delete pHandlerA;
    delete pHandlerB;
    delete pHandlerC;

    return 0;
}
