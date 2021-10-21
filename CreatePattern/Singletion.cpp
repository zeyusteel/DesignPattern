//单例模式
/*
特点：对唯一实例的受控访问
*/
#include <iostream>

class CSingletion
{
public:
    inline static CSingletion& get_instance() {
        static CSingletion sigletion;
        return sigletion;
    }

    virtual ~CSingletion() = default;
    CSingletion(const CSingletion&) = delete;
    CSingletion(CSingletion &&) = delete;
    CSingletion& operator=(const CSingletion&) = delete;
    CSingletion& operator=(CSingletion &&) = delete;

    inline void test() {
        std::cout << "test" << std::endl;
    }

protected:
    CSingletion() = default;
};


int main(int argc, char const *argv[])
{
    CSingletion::get_instance().test();
    return 0;
}
