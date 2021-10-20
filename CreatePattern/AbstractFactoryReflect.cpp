//抽象工厂 反射机制实现：利用依赖注入，解决再客户端抽象工厂类别多，在替换工厂时无法与客户端解耦问题

#include <iostream>
#include <string>
#include <map>
#include <functional>

using CreateObj = void* (*)();
//typedef void* (*CreateObj)(); //也可以用function
//using CreateObj = std::function<void *()>;

/***************** cpu 产品 ***************/
class CCpu
{
public:
    virtual ~CCpu() = default;
    virtual void run_cpu() const = 0;
};

class CHwCpu : public CCpu
{
public:
    virtual ~CHwCpu() = default;
    inline virtual void run_cpu() const override {
        std::cout << "run hw cpu" << std::endl;
    }
};

class CHpCpu : public CCpu
{
public:
    virtual ~CHpCpu() = default;
    inline virtual void run_cpu() const override {
        std::cout << "run hp cpu" << std::endl;
    }
};

/***************** 内存产品 ***************/
class CMemory
{
public:
    virtual ~CMemory() = default;
    virtual void use_memory() const = 0;
};

class CHwMemory : public CMemory
{
public:
    virtual ~CHwMemory() = default;
    inline virtual void use_memory() const override {
        std::cout << "use hw memory" << std::endl;
    }
};

class CHpMemory : public CMemory
{
public:
    virtual ~CHpMemory() = default;
    inline virtual void use_memory() const override {
        std::cout << "use hp memory" << std::endl;
    }
};

//反射工厂 负责构造不同类型的工厂
class CReflectFactory
{
public:
    //单例
    inline static CReflectFactory* get_instance() {
        static CReflectFactory *pFactory = nullptr;

        if (!pFactory) {
            pFactory = new CReflectFactory();
        }
        
        return pFactory;
    }

    //默认的工厂，可以替换,也可以通过配置文件读取
    inline void* get_factoryByName(const std::string &strName = "CHpFactory") const {
        auto itor = m_map.find(strName);
        if (itor == m_map.end()) {
            return nullptr;
        }

        return itor->second(); //调用构造的回调函数并返回指针
    }
    
    inline void regist_class(const std::string &strName, CreateObj func) {
        m_map.insert(make_pair(strName, func));
    }

private:
    CReflectFactory() = default;
    
private:
    std::map<std::string, CreateObj> m_map; 
};

/******************** 抽象工厂 *******************/
class CFactory
{
public:
    virtual ~CFactory() = default;

public:
    virtual CCpu* create_cpu() const = 0;
    virtual CMemory* create_memory() const = 0;
};

class CHwFactory : public CFactory
{
public:
    virtual ~CHwFactory() = default;
    
public:
    inline CCpu* create_cpu() const override {
        return new CHwCpu();
    }

    inline CMemory* create_memory() const override {
        return new CHwMemory();
    }
};

class CHpFactory : public CFactory
{
public:
    virtual ~CHpFactory() = default;
    
public:
    inline CCpu* create_cpu() const override {
        return new CHpCpu();
    }

    inline CMemory* create_memory() const override {
        return new CHpMemory();
    }
};

//利用宏定义完成通过类名注册    #可以将参数转成字符串， ##可以将参数直接拼接 
//这里采用回调函数+ lamda给全局变量赋值实现注册; 全局变量也可以用类,将注册函数封装到类的构造函数中

#define REGESTER(className)                                                                     \
    className* create_ ## className() {                                                         \
        return new className;                                                                   \
    }                                                                                           \
    static int g_register ## className = [](){                                                  \
        CReflectFactory::get_instance()->regist_class(#className, (CreateObj)create_ ## className);    \
        return 0;                                                                               \
    }();                                                                                        

REGESTER(CHpFactory)

int main(int argc, char const *argv[])
{
    CFactory *pFactory = static_cast<CFactory*>(CReflectFactory::get_instance()->get_factoryByName());
    if (!pFactory) {
        return -1;
    }

    CCpu *pCpu = pFactory->create_cpu();
    CMemory *pMemory = pFactory->create_memory();

    if (!pCpu || !pMemory) {
        return -1;
    }

    pCpu->run_cpu();
    pMemory->use_memory();

    delete pCpu;
    delete pMemory;
    delete pFactory;

    return 0;
}
