//中介者模式
/*
特点：中介者模式使各个对象之间的交互解耦
*/
#include <iostream>
#include <string>
#include <map>

class CColleague;
class CMediator
{
public:
    virtual ~CMediator() = default;
    virtual void send_msg(const std::string &strMsg, const std::string &strColleague) = 0;
    virtual void set_colleague(const std::string &, CColleague *) = 0;
};

class CColleague
{
public:
    virtual ~CColleague() = default;
    inline void set_mediator(CMediator *pMediator){ m_pMediator = pMediator; }
    virtual void get_msg(const std::string &) = 0;
    virtual void send_msg(const std::string &strMsg, const std::string &strColleague) = 0;

protected:
    CMediator *m_pMediator;
};


class CConcreteColleagueA : public CColleague
{
public:
    virtual ~CConcreteColleagueA() = default;
    
    inline void send_msg(const std::string &strMsg, const std::string &strColleague) override {
        m_pMediator->send_msg(strMsg, strColleague);
    }

    inline void get_msg(const std::string &strMsg) override {
        std::cout << "CConcreteColleagueA get msg "  << strMsg << std::endl;
    }
};

class CConcreteColleagueB : public CColleague
{
public:
    virtual ~CConcreteColleagueB() = default;
    
    inline void send_msg(const std::string &strMsg, const std::string &strColleague) override {
        m_pMediator->send_msg(strMsg, strColleague);
    }

    inline void get_msg(const std::string &strMsg) override {
        std::cout << "CConcreteColleagueB get msg "  << strMsg << std::endl;
    }
};

class CConcreteMediator : public CMediator
{
public:
    virtual ~CConcreteMediator() = default;
    virtual void send_msg(const std::string &strMsg, const std::string &strColleague) override {
        auto itor = m_map.find(strColleague);
        if (itor != m_map.end()) {
            itor->second->get_msg(strMsg);
        }
    }

    virtual void set_colleague(const std::string &strColleague, CColleague *pColleague) override {
        if (!pColleague) { 
            return;
        }
        auto itor = m_map.find(strColleague);

        if (itor == m_map.end())
        {
            m_map.insert(std::make_pair(strColleague, pColleague));
            pColleague->set_mediator(this);
        }
    }

private:
    std::map<std::string, CColleague*> m_map;
};

int main(int argc, char const *argv[])
{
    CConcreteMediator *pMediator = new CConcreteMediator();
    CConcreteColleagueA *pColleagueA = new CConcreteColleagueA();
    CConcreteColleagueB *pColleagueB = new CConcreteColleagueB();


    pMediator->set_colleague("ColleagueA", pColleagueA);
    pMediator->set_colleague("ColleagueB", pColleagueB);

    pColleagueA->send_msg("send a msg", "ColleagueB");

    delete pMediator;
    delete pColleagueA;
    delete pColleagueB;
    return 0;
}
