# DesignPattern
Design Pattern with c++11

## 01概要
参考《大话设计模式》,通过C++实现每一种设计模式
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
### 1. 创建型模式  
 
将类的实例化过程单独封装,隐藏了创建的细节，将对象的创建与使用分离。  
通过多态，使用者只需要知道抽象的接口，不需要知道细节,将构建与表示分离。

抽象工厂:创建一系列或相关依赖的接口   
工厂方法:让工厂的子类决定实例化哪一个产品  
建造者:同样构建过程可以构建不同的表示   
原型:通过拷贝原型创建新对象  
单例:一个类仅有一个实例  

### 2. 结构型模式

在一个类中定义另一个类的对象建立关联关系,构建耦合性更低、功能更强大的结构

适配器:将一个类的接口转换成客户需要的接口  
桥接:分离抽象与实现  
组合:树型结构表示 ‘部分-整体’  
装饰:动态给对象添加新功能  
外观:为一组复杂的接口提供高层接口  
轻量:共享已经创建的对象  
代理:通过代理控制对象  

### 2. 行为型模式

行为型模式不仅仅关注类和对象的结构，而且重点关注它们之间的相互作用。

观察者:一个对象状态改变，依赖于它的对象得到通知
模版方法:父类定义方法框架，子类去实现
命令:将一个请求封装为一个对象
状态:将状态封装为一个对象，context维护当前的状态与状态切换
责任链:将责任踢给后继节点
解释器:定义语言的文法，用解释器去解释
中介者:用中介者封装一系列对象的交互
访问者:以不同的身份访问数据元素,实现对元素的不同操作
策略:定义一系类算法
备忘录:捕获对象的内部状态
迭代器:提供访问聚合对象元素的方法

***






