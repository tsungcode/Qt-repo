#include <iostream>

using namespace std;


class A
{
public:
    A()
    {
        cout<<"A的默认构造函数:"<<intptr_t(this)<<endl;
    }
    A(const A&ob)
    {

        cout<<"A的拷贝构造函数:"<<intptr_t(&ob)<<">>>>"<<intptr_t(this)<<endl;
    }
    A& operator=(const A&ob)
    {
        cout<<"A的拷贝赋值函数:"<<intptr_t(&ob)<<">>>>"<<intptr_t(this)<<endl;
    }

    A(A&&ob)
    {
        cout<<"A的MOVE构造函数:"<<intptr_t(&ob)<<">>>>"<<intptr_t(this)<<endl;
    }
    A & operator=(A &&ob)
    {
        cout<<"A的MOVE赋值函数:"<<intptr_t(&ob)<<">>>>"<<intptr_t(this)<<endl;
    }
    ~A()
    {
        cout<<"A的析构函数:"<<intptr_t(this)<<endl;
    }
};
//////////////////////////////////////////////////
A getA()
{
    return A();
    //    A a;
    //    return a;
}

int main()
{
    {
        cout<<"**********1、拷贝构造示例**************"<<endl;
        A a=getA();         //默认构造->拷贝构造(返回临时对象)->拷贝构造(初始化a)
    }
    cout<<"*******************************************"<<endl;
    {
        cout<<"**********2、右值引用示例**************"<<endl;
        A &&b=getA();       //默认构造->拷贝构造(返回临时对象)->右值引用 引用临时对象
    }
    cout<<"*******************************************"<<endl;
    {
        cout<<"**********3、常量左引用示例*************"<<endl;
        const A &c=getA(); //默认构造->拷贝构造(返回临时对象)->常量左引用绑定 引用临时对象
    }
    cout<<"*******************************************"<<endl;
    {
        cout<<"**********4、拷贝赋值示例**************"<<endl;
        A d;
        A e;
        d=e;              //拷贝赋值
    }
    cout<<"*******************************************"<<endl;
    {
        cout<<"**********5、移动赋值示例**************"<<endl;
        A f;
        A g;
        f=std::move(f);   //移动赋值
    }

    return 0;
}
