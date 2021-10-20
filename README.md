# DesignPattern
Design Pattern with c++11

## 01概要
参考《大话设计模式》、《图解设计模式》,[威武的涛哥](https://github.com/jaredtao/DesignPattern),通过C++实现每一种设计模式
***
## 02基本思想
通过封装、继承、多态把程序的耦合降低  
### 单一职责原则：一个类因该仅有一个引起它变化的原因
### 开放封闭原则：对于扩展是开放的，对于更改是封闭的
### 依赖倒转原则：依赖抽象接口编程
### 里氏代换原则：子类能替换父类 (只针对公有继承,是一种is-a的关系 --《Effective C++》)
### 迪米特原则：两个没有必要直接通信的类有调用关系时可以通过第三者转发调用
***
## 03模式分类
1. 创建型模式  
将类的实例化过程单独封装,隐藏了创建的细节，将对象的创建与使用分离。  
通过多态，使用者只需要知道通用的接口，不需要知道实现细节。




