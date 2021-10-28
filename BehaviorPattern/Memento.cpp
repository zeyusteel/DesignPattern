//备忘录模式
/*
特点：对一个对象的内部状态捕获或恢复
*/
#include <iostream>

class CMemento
{
public:
    explicit CMemento(int iLevel) : m_iLevel(iLevel) {}
    inline int get_level() const { return m_iLevel; }
    inline void set_level(int iLevel) { m_iLevel = iLevel; }

private:
    int m_iLevel;
};

class CConcrete
{
public:
    explicit CConcrete(int iLevel) : m_iLevel(iLevel) {}

    inline CMemento create_memento() {
        return CMemento(m_iLevel);
    }

    inline void set_memento(const CMemento &memento) {
        m_iLevel = memento.get_level();
    }

    inline void print_level() const { std::cout << m_iLevel << std::endl; } 
    inline void set_level(int iLevel) { m_iLevel = iLevel; } 
private:
    int m_iLevel;
};

int main(int argc, char const *argv[])
{
    CConcrete object(15); 
    object.print_level();

    CMemento memento = object.create_memento(); //创建快照
    object.set_level(20);
    object.print_level();
    
    object.set_memento(memento); //恢复快照
    object.print_level();

    return 0;
}
