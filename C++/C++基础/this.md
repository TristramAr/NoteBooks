相信在坐的很多人，都在学Python，对于Python来说有self，类比到C++中就是this指针，那么下面一起来深入分析this指针在类中的使用！

首先来谈谈this指针的用处：

（1）一个对象的this指针并不是对象本身的一部分，不会影响sizeof(对象)的结果。

（2）this作用域是在类内部，当在**类的非静态成员函数中访问类的非静态成员**的时候，编译器会自动将对象本身的地址作为一个隐含参数传递给函数。也就是说，即使你没有写上this指针，编译器在编译的时候也是加上this的，它作为非静态成员函数的隐含形参，对各成员的访问均通过this进行。

其次，this指针的使用：

（1）在类的非静态成员函数中返回类对象本身的时候，直接使用 return *this。

（2）当参数与成员变量名相同时，如this->n = n （不能写成n = n)。



**类的静态成员函数没有this指针**

this指针只能作用与非静态成员函数 。

用static修饰成员函数，**使这个类只存在这一份函数，所有对象共享该函数**。由于static修饰的类成员属于类，不属于对象，因此static类成员函数是没有this指针的，this指针是指向本对象的指针。正因为没有this指针，所以**static类成员函数，只能访问 static修饰的类成员变量**，不能访问非static的类成员。  

```cpp
#include <iostream>
using namespace std;

class Test
{
public:
    static int sum(int a)
    {
        num += a;
        return this->num;  //error
        return num;
    }
    int sum2(int b)
    {
        data += b;
        return this->data;
    }
private:
    static int num;
    int data;
};

int main()
{
    
}
```

