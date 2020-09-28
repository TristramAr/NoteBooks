![数据结构与算法.png](https://cdn.acwing.com/media/article/image/2019/09/15/1833_253b16e8d7-%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E4%B8%8E%E7%AE%97%E6%B3%95.png)

# **  c++ 面试题汇总**

## **c++ 基础知识**

### **1、c++和c的区别**

*设计思想上：*  
- c++是面向对象的语言，而c是面向过程的结构化编程语言。  

*语法上：*  
- c++具备**封装、继承和多态**三种特性  
- c++相比c,增加类型安全的功能，比如强制类型转换。  
- c++支持范式编程，比如模板类、函数模板等。

### **2、extern关键字的作用**

extern置于变量或函数前，用于**标示变量或函数的定义在别的文件中**，提示编译器遇到此变量和函数时在其他模块中寻找其定义。  
具体来说有以下两种情况：  

- 当extern与"C"连用时``` extern "C" void fun(int a,int b);```告诉编译器在编译该函数时采用C的规则去编译，而非C++。（C++调用C函数需要extern C，因为C语言没有函数重载。）  
- 当extern作用变量和函数时，``` extern int a;``` 其作用就是**声明函数或者全局变量的作用范围的关键字**，通过该关键字可以使得函数和变量可以在本模块或者其他模块中使用。  (变量和函数在其他文件中已经定义，当前文件使用该变量就需要加`extern`关键字)

### **3、static关键字的作用**

- 修饰局部变量  
  static关键词修饰局部变量时，使得被修饰变量成为静态变量，**存储在静态区。存储在静态区的数据生命周期与程序相同**，在main函数之前初始化，在程序退出时销毁。（无论是局部静态还是全局静态）  

- 修饰全局变量   
  全局变量本来就存储在静态区，因此static并不能改变其存储位置。但是，static限制了其链接属性。被**static修饰的全局变量只能被包含该定义的文件访问**（即**改变了作用域**）。

- 修饰函数  
  static修饰函数时，使得函数只能在**包含该函数定义的文件中被调用**。对于静态函数，声明和定义需要放在同一文件夹中。  （`static`修饰的函数，限定在本源码文件中使用。）

- 修饰成员变量 

  static修饰类的成员变量，**会使该数据被所有类的对象共享**。（提供一个共享数据给所有对象使用的）可以通过类名和对象进行访问，而非静态成员变量只能通过对象进行访问。并且static 成员函数需要在类外面进行初始化 ```int Text::count=5;```，并且在类实例化之前初始化。

- 修饰成员函数  
 用static修饰成员函数，**使这个类只存在这一份函数，所有对象共享该函数**。由于static修饰的类成员属于类，不属于对象，因此static类成员函数是没有this指针的，this指针是指向本对象的指针。正因为没有this指针，所以**static类成员函数，只能访问 static修饰的类成员变量**，不能访问非static的类成员。  

- 最重要的特性：隐藏  
 当同时编译多个文件时，所有未加static前缀的全局变量和函数都具有全局可见性，其它的源文件也能访问。利用这一特性可以在不同的文件中定义同名函数和同名变量（**static修饰全局变量和函数后，就只能在有其定义的文件中访问**），而不必担心命名冲突。static可以用作函数和变量的前缀，对于函数来讲，static的作用仅限于隐藏。  

### **4、const的作用**

 - 修饰变量，说明该变量不可修改；  

 - 常量引用，经常用于形参类型，即避免了拷贝，又避免了函数对值的修改；

 - **修饰成员函数，该成员函数不能修改成员变量**。const成员函数（只需要在成员函数参数列表后加上关键字const，如char get() const;可以访问const成员变量和非const成员变量，但不能修改任何变量。在声明一个成员函数时，若该成员函数并不对数据成员进行修改操作，应尽可能将该成员函数声明为const成员函数。

- **const对象只能访问const成员函数**,而非const对象可以访问任意的成员函数,包括const成员函数

- const修饰指针，分为指针常量和常量指针。  
  常量指针：可以修改指针所指向的对象，但不能修改指针所指对象的值。
  指针常量：可以改变指针所指对象储存的值，不能改变所指对象。

  ```cpp
   //int const*p 等价于const int*,const作用于*p,说明*p不能改，即指针p所指对象的值不能改  常量指针，const作用的是值。
  //可以修改指针所指向的对象，不能修改指针所指向对象的值
  int a = 10;
  int b = 20;
  int c = 55;
  int const *p = &a;
  const int *q = &b; 
  p = &c;
  q = &c;  //可以修改所指向对象
  // *q = 12;
  // *p = 13;  //不可修改所指向对象的值
  
  //int *const p, const 作用于p,即指针不能改， 指针常量，const作用于指针。
  //可以改变所指向对象储存的值；不可以改变所指向对象。
  int * const p1 = &a;
  int *const q1 = &b;
  // p1 = &c;
  *p1 = 3;
  cout<<p1<<endl;
  cout<<a<<endl;
  ```

  

### **5、指针和引用的区别**

- 指针只是一个变量，只不过这个变量存储的是一个地址；而引用跟原来的变量实质上是同一个东西，只不过是原变量的一个别名而已，不占用内存空间。
- 引用必须在定义的时候初始化，而且初始化后就不能再改变；而指针不必在定义的时候初始化，初始化后可以改变。
- 指针可以有多级，而引用只能是一级。
- “sizeof 引用" = 指向变量的大小 ， "sizeof 指针"= 指针本身的大小。
- **指针可以为空，但引用不能为空**（这就意味着我们拿到一个引用的时候，是不需要判断引用是否为空的，而拿到一个指针的时候，我们则需要判断它是否为空。这点经常在判断函数参数是否有效的时候使用。）
- 如果返回动态内存分配的对象或者内存，必须使用指针，引用可能引起内存泄露

### **6、new与malloc的区别**

- malloc与free是C++/C语言的标准库函数，new/delete是C++的运算符。它们都可用于申请动态内存和释放内存。前者在使用时必须指明申请内存空间的大小。
- new可以认为是malloc加构造函数的执行。new出来的指针是直接带类型信息的。而malloc返回的都是void指针。
- 由于**malloc/free是库函数**而不是运算符，不在编译器控制权限之内，不能够把执行构造函数和析构函数的任务强加于malloc/free。因此C++语言需要一个能完成动态内存分配和初始化工作的**运算符new**，以一个能完成清理与释放内存工作的**运算符delete**。注意new/delete不是库函数。
- new在动态分配内存的时候可以初始化对象，调用其构造函数，delete在释放内存时调用对象的析构函数。而malloc只分配一段给定大小的内存，并返回该内存首地址指针，如果失败，返回NULL。（malloc是c时代的根本没有构造函数和析构函数的定义）
- malloc 2G能不能成功？Windows下32位程序如果单纯看地址空间能有4G左右的内存可用，不过实际上系统会把其中2G的地址留给内核使用，所以你的程序最大能用2G的内存。除去其他开销，你能用malloc申请到的内存只有1.9G左右。

### **7、数组和指针的区别**

**指针**
- 保存数据的地址；
- 间接访问 数据，首先获得指针的内容，然后将其作为地址，从该地址中提取数据。
- 通常用于 动态的数据结构
- 通过malloc/free   new/delete 分配内存和释放内存

**数组**  

- 保存数据
- 直接访问数据
- 通常用于固定数目和类型相同的元素
- 隐式分配和删除
- 数组名称实际上代表数组的起始地址,数组名其实就是一个指针。  

### **8、C++的多态性**

**多态的表现形式一：**

- 派生类的指针可以赋给基类指针。

- 通过基类指针可以调用基类和派生类的同名**虚函数**： 
  
  <1> 若指针指向一个基类的对象，那么被调用的是基类的虚函数。 

  <2> 若指针指向一个派生类的对象，那么被调用的是派生类的虚函数。
  
  ```cpp
  //基类
  class CBase {
  public:
      void FuncA()
       {
           printf( "FuncA called\n" );
       }
  	virtual void SomeVirtualFunction() { }
  };
  //派生类
  class CDerived:public CBase {
  public :
      //重写
      void FuncA()
       {
          CBase::FuncA();
          printf( "FuncAB called\n" );
       }
      virtual void SomeVirtualFunction() { }
  };
  
  int main() {
      CDerived ODerived;
      CBase * p = & ODerived;     // 派生类指针可以赋给基类指针，这里p指向派生类对象，所以执行派生类的虚函数
      p -> SomeVirtualFunction(); //调用哪个虚函数取决于 p 指向哪种类型的对象
      p->FuncA(); //由于该函数不是虚函数，所以基类指针p仍然调用基类的FuncA()函数
  
      return 0;
}
  ```
  
  

**多态的表现形式二：**  

- 派生类对象可以赋值给基类引用

- 通过基类引用调用基类和派生类中的同名虚函数时： 
  
  <1> 若该引用的是一个基类的对象，那么被调用的是基类的虚函数；

  <2> 若该引用引用的是一个派生类的对象，那么被调用的是派生类的虚函数；
  
  ```cpp
  //基类
  class CBase {
  public:
  virtual void SomeVirtualFunction() { }
  };
  //派生类
  class CDerived:public CBase {
  public :
  virtual void SomeVirtualFunction() { }
  };
  
  int main() {
  CDerived ODerived;
  CBase & r = ODerived;    // 派生类对象赋值给基类引用，此次r引用的是派生类的对象，所以执行派生类虚函数。
  r.SomeVirtualFunction(); //调用哪个虚函数取决于 r 引用哪种类型的对象
  return 0;
}
  ```
  
  以上两种情况都称为多态  
  多态性可以简单地概括为**一个接口，多种方法**，程序在运行时才决定调用的函数 。  
  **多态与非多态的实质区别就是函数地址是早绑定还是晚绑定**。如果函数的调用，在编译器编译期间就可以确定函数的调用地址，并生产代码，是静态的，就是说地址是早绑定的。而如果函数调用的地址不能在编译器期间确定，需要在运行时才确定，这就属于晚绑定。

### **9、动态绑定与静态绑定**

- 静态绑定发生在编译期，动态绑定发生在运行期；
- 对象的动态类型可以更改，但是静态类型无法更改；
- 要想实现多态 ，必须使用动态绑定；
- 在继承体系中只有虚函数使用的是动态绑定，其他的全部是静态绑定；
- 静态多态是指通过模板技术或者函数重载技术实现的多态，其在编译器确定行为。动态多态是指通过虚函数技术实现在运行期动态绑定的技术

  **动态绑定：**有一个基类，两个派生类，基类有一个virtual函数，两个派生类都覆盖了这个虚函数。现在有一个基类的指针或者引用，当该基类指针或者引用指向不同的派生类对象时，调用该虚函数，那么最终调用的是该被指向对象对应的派生类自己实现的虚函数。（即上面两种多态表现形式）

### **10、C++11智能指针**

C++里面的四个智能指针: auto_ptr, shared_ptr, weak_ptr, unique_ptr 其中后三个是c++11支持，并且第一个已经被11弃用。
**智能指针shared_ptr？**  

- 头文件： <memory>，share_ptr是一个模板类
- 通过 shared_ptr 的构造函数，可以让 shared_ptr 对象托管一个 new 运算符返回的指针，写法如下：shared_ptr<T> ptr(new T); // T 可以是 int ,char, 类名等各种类型。此后 ptr 就可以像 T* 类型的指针一样来使用，即 *ptr 就是用 new 动态分配的那个对象，而且不必操心释放内存的事。
- 多个 shared_ptr 对象可以同时托管一个指针，系统会维护一个托管计数。当无shared_ptr托管该指针时， delete 该指针。

**为什么要使用智能指针：** 

- 智能指针的作用是管理一个指针，因为存在以下这种情况：申请的空间在函数结束时忘记释放，造成内存泄漏。使用智能指针可以很大程度上的避免这个问题，因为智能指针就是一个类，当超出了类的作用域时，类会自动调用析构函数，析构函数会自动释放资源。**所以智能指针的作用原理就是在函数结束时自动释放内存空间，不需要手动释放内存空间**。  
  

**智能指针的实现**
智能指针：实际指行为类似于指针的类对象 ，它的一种通用实现方法是采用引用计数的方法。 
1、智能指针将一个计数器与类指向的对象相关联，引用计数跟踪共有多少个类对象共享同一指针  
2、每次创建类的新对象时，初始化指针并将引用计数置为1；  
3、当对象作为另一对象的副本而创建时，拷贝构造函数拷贝指针并增加与之相应的引用计数；  
4、对一个对象进行赋值时，赋值操作符减少左操作数(因为指针已经指向别的地方)所指对象的引用计数（如果引用计数为减至0，则删除对象），并增加右操作所指对象的引用计数；这是因为左侧的指针指向了右侧指针所指向的对象，因此右指针所指向的对象的引用计数+1；  
5、调用析构函数时，构造函数减少引用计数（如果引用计数减至0，则删除基础对象）。

### **11、内联函数，宏定义和普通函数的区别**

**内联函数**  
由于函数的调用是有时间开销的，如果函数本身只有几条语句，执行非常快，但是函数被调用了很多次，相比之下调用的开销就会显得比较大，**为了减少函数调用的开销引入内联函数**。为了减少函数调用的开销，编译器在对内联函数的调用时是将整个函数的代码插入到调用语句处，而不产生调用函数的语句。  

**区别**
- 内联函数要做参数类型检测，而宏不需要，这是内联函数的优势。
- 宏定义是在预编译时把所有宏名用宏体代替，内联函数则是在编译时进行代码插入。编译器会在每处调用内联函数的地方直接把内联函数的内容展开，这样可以省去函数的调用的压栈出栈的开销，提高效率。
- 内联函数是指嵌入代码，就是在调用函数的地方不是跳转，而是把代码直接写到那里去。对于短小简单的代码来说，内联函数可以带来一定的效率提升，而且和C时代的宏函数相比，内联函数 更安全可靠。可是这个是以增加空间消耗为代价的

### **12、常用的设计模式**

设计模式（Design pattern）是一套被反复使用、多数人知晓的、经过分类编目的、代码设计经验的总结。比如单例模式、工厂模式。  
- [单例模式](https://blog.csdn.net/u012940886/article/details/80386669)：保证一个类仅有一个实例，并提供一个访问它的全局访问点。

  ```cpp
  /*
   * @Description: 
   * @Author: feng
   * @Date: 2019-11-04 21:01:16
   * @LastEditTime: 2020-09-08 14:53:15
   * @LastEditors: feng
   */
  #include <iostream>
  #include <thread>
  #include <mutex>
  using namespace std;
  
  class Singleton
  {
  private:
      Singleton()
      {
          cout << "创建了一个单例对象" << endl;
      }
      Singleton(const Singleton &);
      Singleton &operator=(const Singleton &);
  public:
       static Singleton *instance; //这是我们的单例对象,它是一个类对象的指针
      // 单例模式
      static Singleton *getInstance()
      {
          //懒汉
          if (instance == NULL)
              instance = new Singleton();
          else
          {
              cout << "false" << endl;
          }
          return instance;
   
          //饿汉
          // static Singleton Instance;
          // return &Instance;
      }
      //改进的懒汉式（双重检查锁）
      // static Singleton *getInstance()
      // {
      //     if (instance == NULL) //判断是否第一调用
      //     {
      //         Lock(); //表示上锁的函数
      //         if (instance == NULL)
      //         {
      //             instance = new Singleton();
      //         }
      //         UnLock(); //解锁函数
      //     }
      //     return instance;
      // }
    ~Singleton()
      {
          // 析构函数我们也需要声明成private的
          //因为我们想要这个实例在程序运行的整个过程中都存在
          //所以我们不允许实例自己主动调用析构函数释放对象
          cout << "销毁了一个单例对象" << endl;
      }
  private:
      //定义一个内部类
      class Garbo
      {
      public:
          Garbo() {}
          ~Garbo()
          {
              if (instance != NULL)
              {
                  delete instance;
                  instance = NULL;
              }
          }
      };
  
      //定义一个内部类的静态对象
      //当该对象销毁的时候，调用析构函数顺便销毁我们的单例对象
      static Garbo _garbo;
  };
  
  //下面这个静态成员变量在类加载的时候就已经初始化好了
  Singleton *Singleton::instance = NULL;
  Singleton::Garbo Singleton::_garbo; //还需要初始化一个垃圾清理的静态成员变量
  
  int main()
  {
      cout << "Now we get the instance" << endl;
      Singleton *instance1 = Singleton::getInstance();
      // Singleton *instance2 = Singleton::getInstance();
      // Singleton *instance3 = Singleton::getInstance();
      cout << "Now we destroy the instance" << endl;
      return 0;
  }
  ```

- [工厂模式](https://www.cnblogs.com/xiaolincoding/p/11524376.html)：定义一个用于创建对象的接口，让子类决定实例化哪一个类。Factory Method 使一个类的实例化延迟到其子类。（比如一个生成鞋子的代工厂，可以生成nike Adidas deng, 根据鞋子的热度选择生产哪一种鞋子）

  ```cpp
  #include <iostream>
  #include <vector>
  using namespace std;
  //鞋子
  class Shoes
  {
  public:
      virtual ~Shoes();
      virtual void show() = 0; //纯虚函数
  };
  //nike鞋，继承Shoes
  class NikeShoes : public Shoes
  {
  public:
      void show()
      {
          cout << "nike:just do it" << endl;
      }
  };
  class AdidasShoes : public Shoes
  {
  public:
      void show()
      {
          cout << "adidas:Impossible is nothing" << endl;
      }
  };
  // 李宁鞋子
  class LiNingShoes : public Shoes
  {
  public:
      void show()
      {
          std::cout << "我是李宁球鞋，我的广告语：Everything is possible" << std::endl;
      }
  };
  
  enum SHOES_TYPE
  {
      NIKE,
      LINING,
      ADIDAS
  };
  
  //定义工厂类
  class ShoesFactory
  {
  public:
      Shoes *CreateShoes(SHOES_TYPE type)
      {
          switch (type)
          {
          case NIKE:
              return new NikeShoes();
              break;
          case LINING:
              return new LiNingShoes();
              break;
          case ADIDAS:
              return new AdidasShoes();
              break;
          default:
              return NULL;
              break;
          }
      }
  };
  int main()
  {
      // 构造工厂对象
      ShoesFactory shoesFactory;
  
      // 从鞋工厂对象创建阿迪达斯鞋对象
      Shoes *pNikeShoes = shoesFactory.CreateShoes(NIKE);
      if (pNikeShoes != NULL)
      {
          // 耐克球鞋广告喊起
          pNikeShoes->show();
  
          // 释放资源
          delete pNikeShoes;
          pNikeShoes = NULL;
      }
      return 0;
  }
  ```

  

### **13、C++内存管理**

 **栈：** **存放函数参数及局部变量**，在出作用域时自动释放，栈内存分配运算内置于处理器的指令集中，效率很高，但是分配的内存容量有限。

**堆：**操作系统所维护的一块特殊内存，用于程序的内存动态分配，C语言使用malloc从堆上分配内存，使用free释放已分配的对应内存。

**自由储存区：** 自由存储区是C++基于new操作符的一个抽象概念，凡是通过new操作符进行内存申请，该内存即为自由存储区

 **全局/静态区：** 全局变量和静态变量被分配到同一块内存中，存储在静态区的数据生命周期与程序相同，在main函数之前初始化，在程序退出时销毁。

**常量储存区：** 常量（const）储存在该处，该区域不能改。

### **14、[堆和栈的区别](https://www.cnblogs.com/Azhu/p/4436531.html)**

 - 空间分配的区别  
 栈（操作系统)：由**操作系统自动分配释放**，存放函数的**参数值，局部变量**的值等。其操作方式类似于数据结构中的栈；

  堆（操作系统）：一般由**程序员分配释放**， 若程序员不释放，程序结束时可能由OS回收，分配方式倒是类似于链表。

 - 空间大小不同  
 堆的内存能达到几个G,栈非常小（VC6中,栈默认大小是1M,当然,你可以修改它）

 - 能否产生碎片  
 对于堆来讲，频繁的new/delete势必会造成内存空间的不连续，从而造成大量的碎片，使程序效率降低。对于栈来讲，则不会存在这个问题，因为栈是先进后出的队列，他们是如此的一一对应，以至于永远都不可能有一个内存块从栈中间弹出，在他弹出之前，在他上面的后进的栈内容已经被弹出，

 - 生长方向不同  
 堆的生长方向是向上的，也就是向着内存地址增加的方向生长。对于栈来讲，它的生长方向是向下的，是向着内存地址减小的方向增长。

 - 分配效率  
 栈是机器系统提供的数据结构，计算机会在底层对栈提供支持：分配专门的寄存器存放栈的地址，压栈出栈都有专门的指令执行，这就决定了栈的效率比较高。堆则不然,它由C/C++函数库提供,机制复杂,堆的效率要比栈低得多

 - 分配方式 

 **堆都是动态分配的，没有静态分配的堆。栈有2种分配方式：静态分配和动态分配**静态分配是编译器完成的，比如局部变量的分配。动态分配由alloca函数进行分配，但是栈的动态分配和堆是不同的，他的动态分配是由编译器进行释放，无需我们手工实现。

### **15、解释下封装、继承和多态**

 - 封装  
 封装是实现面向对象程序设计的第一步，封装就是将数据或函数等集合在一个个的单元中（我们称之为类）封装的意义在于保护或者防止代码（数据）被我们无意中破坏。
 - 继承   
 继承主要实现重用代码，节省开发时间。子类可以继承父类的一些东西。
 - 多态  
 同一操作作用于不同的对象，可以有不同的解释，产生不同的执行结果。在运行时，可以**通过指向基类的指针，来调用实现派生类中的方法**。

### 16、指针数组和数组指针

- 指针数组：即*指针的数组*，落脚点在数组。即该变量为一个数组，且数组中存放的所有元素都是指针类型。

- 数组指针：即*数组的指针*，落脚点在指针。即该变量为一个指针，该指针指向数组的首地址。**数组指针和数组变量名不同**，数组变量名是数组第一个元素的地址。因为a是数组首元素首地址，pa存放的却是数组首地址，a是char 类型，a+1，a的值会实实在在的加1，而pa是char[4]类型的，pa+1，pa则会加4，虽然数组的首地址和首元素首地址的值相同，但是两者操作不同

  ```cpp
  //arr就是我定义的一个指针数组，它有四个元素，每个元素是一个char *类型的指针，这些指针存放着其对应字符串的首地址。
  char *arr[4] = {"hello", "world", "shannxi", "xian"};
  //数组指针
  char (*pa)[4];
  //数组
  char a[4];
  ```

  

### 17、指针常量和常量指针

- 常量指针：即常量的指针，**const作用于值**。```int const*p 等价于const int*p ```,const作用于(*p),所以(*p)不能改,即不能改变指针所指对象的值，可以改变指针所指对象（值是常量）
- 指针常量：即指针是常量，**const作用于指针**。```int *const p```  ,const 作用域指针p，所以指针指向的对象不可改变，但是指向对象的值可以更改。（指针是常量）

### 18、野指针（空悬指针）是什么

野指针就是指向一个**已删除的对象**或者未申请访问受限内存区域的指针。
```cpp
int main()
{
    int *ptr = new int(0);
    delete ptr;          // 此时ptr就是野指针
    return 0;
}
//所以一般
int main()
{
    int *ptr = new int(0);
    delete ptr;         
    ptr=NULL;
    return 0;
}
```

### 19、C++中类和结构体的区别

- 最本质的一个区别就是默认的访问控制：**struct作为数据结构的实现体，它默认的数据访问控制是public的**，而**class作为对象的实现体，它默认的成员变量访问控制是private的。**
- “class”这个关键字还用于定义模板参数，就像“typename”。但关键字“struct”不用于定义模板参数。
### 20、析构函数的作用

**析构函数的特点**

- 类成员函数的一种，名字和类名相同。（这里于构造函数相同）不同的是，函数前面加一个~

- 没有参数和返回值（包括void）

- 一个类最多只有一个析构函数

- 对象消亡时，自动被调用，用来释放对象占用的空间，避免内存泄漏

- 定义类时没写析构函数, 则编译器生成缺省析构函数。

- **子类析构函数无论什么情况下都会调用父类的析构函数**

- **析构函数是用来释放对象所分配的资源**

- 如果你的类里面只用到的基本类型，如int char double等，系统的默认析构函数其实什么都没有做。但如果你使用了其他的类如vector，string等，系统的默认析构函数就会**调用这些类对象的析构函数**

- 如果自己写析构函数，如果你的类里面分配了系统资源，如new了内存空间，打开了文件等，那么在你的析构函数中就必须释放相应的内存空间和关闭相关的文件；这样系统就会自动调用你的析构函数释放资源，避免内存泄漏

  ```cpp
  //自己写析构函数
  class A
  {
  private:
      char *data;
  public:
      //构造函数
      A()
      {
          data = new char[10];
      }
      //析构函数
      ~A()
      {
          delete[] data;
      }
  };
  ```

  

析构函数的析构顺序

```cpp
#include <iostream>
#include <vector>
using namespace std;
class Demo
{
    int id;

public:
    Demo(int i)
    {
        id = i;
        cout << "id=" << id << "construct" << endl;
    }
    ~Demo()
    {
        cout << "id=" << id << "deconstruct" << endl;
    }
};
Demo d1(1);
void func()
{
    static Demo d2(2);
    Demo d3(3);
    cout << "func" << endl;
}
int main()
{
    Demo d4(4);
    // 这边有一个类型转换构造函数，通过定义一个创建临时的Demo对象完成。
    //所以需要对临时对象进行构造和析构，
    d4 = 6;    
    cout << "main" << endl;
    {
        Demo d5(5);
    }
    func();
    cout << "main end" << endl;
    return 0;
}
//id=1construct
id=4construct
id=6construct
id=6deconstruct
main
id=5construct
id=5deconstruct
id=2construct
id=3construct
func
id=3deconstruct
main end
id=6deconstruct
id=2deconstruct
id=1deconstruct
```



### 21、虚函数的作用

虚函数是在类的定义中前面有个virtual关键字的成员函数。virtua只能用在类定义中的函数声明中。**构造函数和静态成员函数不能是虚函数。**

**虚函数作用**  

- 虚函数可以让成员函数操作一般化，用基类的指针指向不同的派生类的对象时，基类指针调用其虚成员函数，则会调用其真正指向对象的成员函数，而不是基类中定义的成员函数（只要派生类改写了该成员函数）。若不是虚函数，则不管基类指针指向的哪个派生类对象，调用时都会调用基类中定义的那个函数。**虚函数是C++多态的一种表现**，可以进行灵活的动态绑定。
- 虚函数通过基类指针或引用实现多态
- 虚函数通过函数重写也能实现多态
### 22、操作系统和编译器如何区分全局变量和局部变量？

操作系统只管调度进程，编译器通过分配位置知道的。**全局变量分配**在全局数据段非陪**在静态区**，并且在程序开始的时候就被加载。**局部变量分配在栈区里面**。

### [23、初始化列表](https://www.cnblogs.com/graphics/archive/2010/07/04/1770900.html)

**初始化列表的作用**

- 使用初始化列表主要是基于性能问题，对于内置类型，如int, float等，使用初始化列表和在构造函数体内初始化差别不是很大；但是对于类类型来说，最好使用初始化列表。这样就可以直接调用拷贝构造函数初始化，省去了一次调用默认构造函数的过程。  
**以下情况必须放在初始化列表**
- 常量成员，因为常量只能初始化不能赋值，所以必须放在初始化列表里面
- 引用类型，引用必须在定义的时候初始化，并且不能重新赋值，所以也要写在初始化列表里面
- 没有默认构造函数的类类型，因为使用初始化列表可以不必调用默认构造函数来初始化，而是直接调用拷贝构造函数初始化。

###  24、重载（overload）与重写（Override）的区别？

**从定义上**

- 重载：是指**同一个类中**允许存在多个同名函数，而这些函数的参数表不同（或许**参数个数**不同，或许**参数类型**不同，或许两者都不同）。**如果同时在类中，对于函数名相同的const函数和非const函数能够构成重载**
- 重写：是指子类重新定义父类虚函数的方法。
  **从原理实现上**
- 重载：编译器根据函数不同的参数表，对同名函数的名称做修饰，然后这些同名函数就成了不同的函数。
- 重写：**表示子类中的方法可以与父类中的某个方法（可以不是虚函数）的名称和参数完全相同，通过子类创建的实例对象调用这个方法时，将调用子类中的定义方法，这相当于把父类中定义的那个完全相同的方法给覆盖了，这也是面向对象编程的多态性的一种表现**。子类覆盖父类的方法时，只能**比父类抛出更少的异常**，或者是抛出父类抛出的异常的子异常，因为子类可以解决父类的一些问题，不能比父类有更多的问题。**子类方法的访问权限只能比父类的更大，不能更小**。如果父类的方法是private类型，那么，子类则不存在覆盖的限制，相当于子类中增加了一个全新的方法。**子类返回类型小于等于父类方法返回类型。**
  **补充：**“隐藏”是指派生类的函数屏蔽了与其同名（不管参数如何，有无virtual关键字）的基类函数。规则如下： 
  - 如果派生类的函数与基类的函数同名，但是参数不同。此时，不论有无virtual关键字，基类的函数将被隐藏（注意别与重载混淆，重载是同一个类中）。 
  - 如果派生类的函数与基类的函数同名，并且参数也相同，但是基类函数没有virtual 关键字。此时，基类的函数被隐藏（注意别与重写混淆）

### 25、内存溢出，内存泄漏的原因？

**内存溢出的原因**  内存溢出是指程序在申请内存时，没有足够的内存空间供其使用。原因如下

- 内存中加载的数据量过于庞大，如溢出从数据库中取出过多数据
- 代码存在死循环或循环产生过多的对象实体
- 递归太深，导致堆栈溢出。
- 内存泄漏导致内存溢出

**内存泄漏的原因**
内存泄漏是指系统申请分配内存进行使用（new），但是用完后不归还（delete）导致占用有效内存。常见情况如下：

- 在类的构造函数和析构函数中没有匹配的调用new和delete。 
两种情况下会出现这种内存泄露：一是在堆里创建了对象占用了内存，但是没有显示地释放对象占用的内存；二是在类的构造函数中动态的分配了内存，但是在析构 函数中没有释放内存或者没有正确的释放内存
- 在new int a[10]时没有对应使用delete[]
- 没有将基类的析构函数定义为虚函数.
当基类指针指向子类对象时，如果基类的析构函数不是virtual，那么子类的析构函数将不会被调用，子类的资源没有正确是释放，因此造成内存泄露。

**堆栈溢出**

- 堆栈溢出是说堆区和栈区的溢出，二者同属于缓冲区溢出。从一旦程序确定，堆栈内存空间的大小就是固定的，当数据已经把堆栈的空间占满时，再往里面存放数据就会超出容量，发生上溢；当堆栈中的已经没有数据时，再取数据就无法取到了，发生下溢。需要注意的是，栈分为顺序栈和链栈，链栈不会发生溢出，顺序栈会发生溢出

### 26、基类的析构函数定义为虚函数的原因（虚析构函数）

- 每个析构函数只会清理自己的成员（成员函数前没有virtual）。

- 可能是基类的指针指向派生类的对象，当析构一个指向派生类的成员的基类指针，这时程序不知道这么办，可能会造成内存的泄露，因此此时**基类的析构函数要定义为虚函数**；
  基类指针可以指向派生类的对象（多态），如果删除该指针delete[]p，就会调用该指针指向的派生类的析构函数，而派生类的对象又会自动调基类的成员函数，这样就会把派生z类的对象释放，如果基类 的析构函数没有定义成虚函数，则编译器实现的静态绑定，在删除基类的指针，只会释放基类的对象而不会释放派生类的对象，此时会导致释放内存不完全，就会导致内存泄露的问题。

  ```cpp
  #include <iostream>
  using namespace std;
  //基类的析构函数没有定义成虚函数
  class son {
  public:
      ~son() { cout << "bye from son" << endl; };
      };
  
  class grandson : public son {
      public:
      ~grandson() { cout << "bye from grandson" << endl; };
  };
  int main() {
      son *pson;
      pson = new grandson;
      delete pson;
      return 0;
  }
  //输出：bye from son
  
  
  // 虚析构函数
  #include <iostream>
  using namespace std;
  class son {
      public:
      virtual ~son() { cout << "bye from son" << endl; };  // 虚析构函数
  };
  class grandson : public son {
  public:
      ~grandson() { cout << "bye from grandson" << endl; };
  };
  int main() {
      son *pson;
      pson = new grandson;
      delete pson;
      return 0;
  }
  //输出：bye from grandson
  //     bye from son
  ```

  
### [27、虚函数表](https://blog.csdn.net/primeprime/article/details/80776625)

参考标题连接和[该链接](https://www.cnblogs.com/LUO77/p/5771237.html)
考虑如下问题:

- 虚函数表是针对类的还是针对对象的？
  - 虚表是属于类的，而不是属于某个具体的对象，一个类只需要一个虚表即可。同一个类的所有对象都使用同一个虚表。
- 同一个类的两个对象的虚函数表是怎么维护的？**共享参数表**
  - 为了指定对象的虚表，对象内部包含一个虚表的指针，来指向自己所使用的虚表。为了让每个包含虚表的类的对象都拥有一个虚表指针，编译器在类中添加了一个指针，*__vptr，用来指向虚表。这样，当类的对象在创建时便拥有了这个指针，且这个指针的值会自动被设置为指向类的虚表。
- 子类虚函数表和基类虚函数表的关系。（子类重写虚函数？）
  - 如果子类无重写，直接继承基类的虚函数表，然后在后面依次加上自己的虚表
  - 如果重写，修改改虚表，其他的前继续。
### 28、什么函数不能为虚函数？

**不能继承的函数和不能重写的函数**

- 普通函数，普通函数不是成员函数，不能被继承。普通函数可以被重载但是不能被重写。
- 构造函数，首先说下什么是构造函数，构造函数是用来初始化对象的。假如子类可以继承基类构造函数，那么子类对象的构造将使用基类的构造函数，而基类构造函数并不知道子类的有什么成员，显然是不符合语义的。从另外一个角度来讲，多态是通过基类指针指向子类对象来实现多态的，在对象构造之前并没有对象产生，因此无法使用多态特性，这是矛盾的。因此构造函数不允许继承。
- 首先静态成员函数理论是可继承的。但是静态成员函数是编译时确定的，无法动态绑定，不支持多态，因此不能被重写，也就不能被声明为虚函数。
- 内联函数，我们需要知道内联函数就是为了在代码中直接展开，减少函数调用花费的代价。也就是说内联函数是在编译时展开的。而虚函数是为了实现多态，是在运行时绑定的。因此显然内联函数和多态的特性相违背。

### [29、深拷贝和浅拷贝的区别](https://blog.csdn.net/caoshangpa/article/details/79226270)

浅拷贝：默认的拷贝就是浅拷贝。 仅仅多了个指针指向原来的空间。（都指向同一内存空间）
深拷贝：自己写的拷贝,自己申请了动态内存空间,用了new 或 malloc 。不但多了指针,而且多了空间。 

### 30 纯虚函数的理解

**纯虚函数：只有函数定义没有函数体的虚函数。**
在很多情况下，基类本身生成对象是不合情理的。例如，动物作为一个基类可以派生出老虎、孔雀等子类，但动物本身生成对象明显不合常理。所以引入了纯虚函数的概念

```cpp
class A {
    private:
    int a;
    public:
    virtual void Print( ) = 0 ; //纯虚函数(工厂模式中常用)
    void fun() { cout << “fun”; }
};
```
**抽象类：包含纯虚函数的类。**

- 只能作为基类，依靠派生类使用。
- 不能创建抽象类对象。
- 可以定义抽象类的指针和引用。
- 在成员函数内可以调用纯虚函数
- 在构造函数/析构函数 内部不能调用纯虚函数
- 如果一个类从抽象类派生而来，它实现了基类中的所有纯虚函数，才能成为非抽象类。

### 31 sizeof关键字

**剑指offer**

1、定义一个空的类型， 里面没有任何成员变量和成员函数。对该类型求sizeof， 得到的结果是多少？

2、如果在该类型中添加一个构造函数和析构函数，再对该类型求sizeof，得到的结果又是多少？

3、那如果把析构函数标记为虚函数呢？

### 32 构造函数、拷贝构造函数

拷贝构造函数的第一个参数是自身的引用

```cpp
class Complex {
public :
double real,image;
Complex(){ }
Complex( const Complex & c )
    {
        real = c.real;
        image = c.image;
        cout<<"copy"<<endl;
    }
};
```



## 刷题笔记

### 1、静态成员变量不分配空间

sizeof的本质是得到某个类型的大小，确切的来说就是当创建这个类型的一个对象(或变量)的时候，需要为它分配的空间的大小。而类也可以理解为类似于int、float这样的一种类型，**当类中出现static成员变量的时候，static成员变量是存储在静态区当中的，它是一个共享的量**，因此，在为这个类创建一个实例对象的时候，是**无需再为static成员变量分配空间**

```cpp
若char是一字节，int是4字节，指针类型是4字节，代码如下：
class CTest
{
    public:
        CTest():m_chData(‘\0’),m_nData(0)
        {
        }
        virtual void mem_fun(){}
    private:
        char m_chData;
        int m_nData;
        static char s_chData;
};
char CTest::s_chData=’\0’;
问：
（1）若按4字节对齐sizeof(CTest)的值是多少？12= 4（虚表指针）+1（char )+3(对齐补位）+4（int)
（2）若按1字节对齐sizeof(CTest)的值是多少？9 =4（虚表指针）+1（char )+4（int)
请选择正确的答案。
```

### 2、重写和重载

**方法重载（overload）：**

- 必须是同一个类

- 方法名（也可以叫函数）一样

- 参数类型不一样或参数数量不一样

**方法的重写（override）** 对象的父类中的函数，两同两小一大原则：

- 方法名相同，参数类型相同

- 子类返回类型小于等于父类方法返回类型，

- 子类抛出异常小于等于父类方法抛出异常，

- 子类访问权限大于等于父类方法访问权限。

### 3、Linux进程控制

**创建进程——fork()**

```
pit_t fork(void);
例如 pid_t pid = fork();
```

- 新进程是当前进程的子进程
- 父进程和子进程
  - 父进程：fork()函数的调用者
  - 子进程：新建的进程
- **子进程是父进程的复制**（相同的数据、堆栈、程序，进程id不一样，与时间有关的数据不一样）

  - 父进程和子进程**并发运行**
- fork返回值pid
  - 在子进程中pid=0；
  - 在父进程中pid>0（子进程的ID号）
  - 出错：pid = -1
  - **子进程执行fork后的代码**（不然其不是无休止的创建进程？）

```cpp
int main(void)
{
    pid_t pid;
    pid = fork();
    //fork后的代码会在父进程执行一遍，然后在子进程执行一遍
    //输出时是父进程先输出还是子进程先输出并不确定（二则并发，前后不确定 ）
    if(pid==0)
    {
        printf("hello world\n");//子进程输出
    }
    else if(pid>0)
    {
       printf("how are you\n"); // 父进程输出
    }
}

//输出
hello world  //子进程输出
how are you  // 父进程输出
```

[**进程执行与父进程不同的功能**](https://www.cnblogs.com/blankqdb/archive/2012/08/23/2652386.html)

通过exec函数族（包含若干函数）

**功能：**装入一个指定的可执行程序运行，是子进程具有和父进程完全不同的功能

**步骤：**

- 根据文件名找到相应的可执行程序
- 将可执行程序的内容填入子进程的地址空间
- 进入新进程执行且不在返回

### 4、[C++构造函数和析构函数的调用顺序](https://www.cnblogs.com/LubinLew/p/Cpp-CallOrderOfConstructorAndDeconstructor.html)

#### 1、**构造函数的调用顺序**

基类构造函数、对象成员构造函数、派生类本身的构造函数 

#### **2、析构函数**的调用顺序

派生类本身的析构函数、对象成员析构函数、基类析构函数（与构造顺序正好相反） 

#### **3、特例**

局部对象，在退出程序块时析构

静态对象，在定义所在文件结束时析构

全局对象，在程序结束时析构 

继承对象，先析构派生类，再析构父类 

对象成员，先析构类对象，再析构对象成员

```cpp
#include <iostream>
using namespace std;
class A
{
public:
     A(){cout<<"A::constructor"<<endl;};
     ~A(){cout<<"A::deconstructor"<<endl;};
};
class B
{
public:
     B(){cout<<"B::constructor"<<endl;};
     ~B(){cout<<"B::deconstructor"<<endl;};
};
class C : public A
{
public:
     C(){cout<<"C::constructor"<<endl;};
     ~C(){cout<<"C::deconstructor"<<endl;};
private:
     B b;
};
class D : public C
{
public:
     D(){cout<<"D::constructor"<<endl;};
     ~D(){cout<<"D::deconstructor"<<endl;};
};

int main(void)
{
    C* pd = new D();
    delete pd;
    return 0;
}
//输出
A::constructor
B::constructor
C::constructor
D::constructor     //new出来的，自己删除
C::deconstructor
B::deconstructor
A::deconstructor
int main(void)
{
    D test;               
    cout<<"delete"<<endl;
    return 0;
}
//输出
A::constructor    // C的基类为A,构造  
B::constructor    // C的对象成员构造
C::constructor    // D的基类
D::constructor    //D本身的构造函数
delete
D::deconstructor
C::deconstructor
B::deconstructor
A::deconstructor

```

### 5、[请你来回答一下++i和i++的区别](https://www.cnblogs.com/zpcoding/p/10805377.html#_label0)

- i++ 返回的是 i 的值，++i 返回的是 i+1 的值

- i++ 不能用作左值，++i 可以用作左值

  ```cpp
  //i++其实是两步 i++ 值的是临时变量temp，所以i++是右值
  int temp = i;
  i = i+1;
  ```

  

### 6、左值、右值、右值引用和std::move

- 左值和右值的区别在于：能否允许用取地址符号 & 来获取相应的内存地址，如果能，则为左值，否则为右值。 
  - 有名皆为左值，变量
  - 常见右值为表达式，常量

- 右值引用：X是一种类型，那么X&&就叫做X的右值引用。 例如`int&&a = 5`

  - 左值引用，常规引用，例如 `int&`
    - 我们不能将左值引用绑定到要求转换的表达式、字面常量或是返回右值的表达式  
  - 右值引用就是必须绑定到右值，不能将一个右值引用绑定到一个左值上  

  ```cpp
  int i = 42;
  int &r = i;         //正确 r引用i
  int &&rr = i;       //错误，i是左值，右值引用不能绑定在左值上
  int &r2 = i*5；     //错误，i*5是表达式，是右值。左值引用不能绑定在右值上
  const int &r3 = i * 42; //正确：我们可以将一个 const的引用绑定到一个右值上
  int &&rr2 = i * 42;    // 正确 ： 将 rr2 绑定到乘法结果上，
  ```

  - 不能将一个右值引用绑定到一个右值引用类型的变量上

    ```cpp
    int &&r1=4;  //正确，字面常量4为右值
    int &&r2=r1; //错误，r1是变量，变量是左值。
    int &&r2 = std::move(r1);  //正确
    ```

    

- std::move的语义：**当对象是右值时，允许左值转移右值的资源和属性而不用进行拷贝复制**

  move 调用告诉编译器：我们有一个左值 ，但我们希望像一个右值一样处理它 。我们必须认识到，调用move 就意味着承诺：除了对 r1 赋值或销毁它外，我们将不再使用它。在调用 move 之后 ，我们不能对移后源对象的值做任何假设 。  

### [强制类型转换](https://blog.csdn.net/Bob__yuan/article/details/88044361)

### [C++中sizeof（struct）怎么计算？](https://www.cnblogs.com/lazycoding/archive/2011/03/22/sizeof-struct.html)

**字节对齐：**变量存放的起始地址相对于结构的起始地址的偏移量。

**Char**
偏移量必须为sizeof(char)即1的倍数

**int**
偏移量必须为sizeof(int)即4的倍数

**float**
偏移量必须为sizeof(float)即4的倍数

**double**
偏移量必须为sizeof(double)即8的倍数

**Short**
偏移量必须为sizeof(short)即2的倍数

long 8个字节

```cpp
struct MyStruct
{
  double dda1;
  char dda;
  int type;
};
cout<<sizeof(MyStruct);
//输出16.
//8+1+3+4 = 16    其中3为相同自动补齐的
```

结构体的大小要为结构体中<strong style="color:red;">占用空间最大类型的整数倍</strong>，不然也需要补齐

```cpp
struct MyStruct
{
    char dda; //偏移量为0，满足对齐方式，dda占用1个字节；

    double dda1; //下一个可用的地址的偏移量为1，不是sizeof(double)=8的倍数，需要补足7个字节才能使偏移量
                 //变为8（满足对齐方式），因此VC自动填充7个字节，dda1存放在偏移量为8的地址上，它占用8个字节。

    int type； //下一个可用的地址的偏移量为16，是sizeof(int)=4的倍数，
               //满足int的对齐方式，所以不需要VC自动填充，type存放在偏移量为16的地址上，它占用4个字节。

};  //所有成员变量都分配了空间，空间总的大小为1+7+8+4=20，不是结构的节边界数（即结构中占用最大空间的类型所占用
    //的字节数sizeof (double)=8）的倍数，所以需要填充4个字节，以满足结构的大小为sizeof(double)=8的倍数。
//所以
//sizeof(MyStruct)=24
```

### [union 和 struct 的区别与联系](https://www.cnblogs.com/firing/articles/2000513.html)

union （ 共用体）：构造数据类型,也叫联合体
 用途：使几个不同类型的变量共占一段内存(相互覆盖)

 struct ( 结构体 )：是一种构造类型
 用途： 把不同的数据组合成一个整体——自定义数据类型

区别：

-  struct和union都是由多个不同的数据类型成员组成, 但在任何同一时刻, union中只存放了一个被选中的成员; 而struct的所有成员都存在。在struct中，各成员都占有自己的内存空间，它们是同时存在的,**一个struct变量的总长度等于所有成员长度之和，遵从字节对其原则**; 在Union中，所有成员不能同时占用它的内存空间，它们不能同时存在 , **Union变量的长度等于最长的成员的长度**。
- 对于union的不同成员赋值, 将会对其它成员重写, 原来成员的值就不存在了,所以，共同体变量中起作用的成员是最后一次存放的成员; 而对于struct的不同成员赋值是互不影响的。

### sizeof()和strlen()的区别

**sizeof()** 求字节运算符，求某个内容实际占用内存的字节数。

**strlen()** 函数，求字符串的大小。strlen() 遇到` \0 `计算结束，并且 `\0 `不会包含在计算的大小内。

### `strcpy()`和`memcpy()`的区别

- **复制的内容不同**

  strcpy只能复制字符串，而memcpy可以复制任意内容，例如字符数组、整型、结构体、类等

- **复制的方法不同**

  strcpy不需要指定长度，它遇到被复制字符的串结束符"\0"才结束，如果空间不够，就会引起内存溢出。memcpy则是根据其第3个参数决定复制的长度。

- **用途不同**

  通常在复制字符串时用strcpy，而需要复制其他类型数据时则一般用memcpy，由于字符串是以“\0”结尾的，所以对于在数据中包含“\0”的数据只能用memcpy

```cpp
//strcyp()实现
char* strcpy(char* destStr,char* srcStr)
{
    if(destStr==NULL||srcStr==NULL)
    {
        return NULL;
    }
    char* address = destStr;
    int i=0;
    for(;strSrc[i]!='\0';i++)
    {
        destSrc[i]=srcStr[i];
    }
    destSrc[i]='\0';
    return address;
}
//strlen
int getStrLen(const char* str)
{
    int len = 0;
    while( *str ++ != '\0')
    {
        len ++;
    }
    return len;
}
```

### memcpy()的实现

以下改进后的`memcpy()`函数，其原本只能进行正向拷贝，内存有重叠是会错。现在可以是实现和`memmove()`类似的功能

```cpp
//按1个字节拷贝
void *my_memcpy(void *dst, void *src, int n)
{
    if (dst == NULL || src == NULL || n <= 0)
    {
        return NULL;
    }
    char *pdst = (char *)dst;
    char *psrc = (char *)src;
    //覆盖一部分,反向拷贝
    if (pdst > psrc && pdst < psrc + n)
    {
        pdst = pdst + n - 1;
        psrc = psrc + n - 1;
        while (n--)
        {
            *pdst-- = *psrc--;
        }
    }
    //正向拷贝
    else
    {
        while (n--)
        {
            *pdst++ = *psrc++;
        }
    }
    return dst;
}
```

### memmove()的实现

```cpp
void* memmove(void* dest, const void* src, size_t n)
{
    char * d  = (char*) dest;
    const char * s = (const char*) src;
  	// 源内存的首地址大于目标内存的首地址时，实行正向拷贝
    if (s>d)
    {
         // start at beginning of s
         while (n--)
            *d++ = *s++;
    }
    //当源内存的首地址小于目标内存的首地址时，实行反向拷贝
    else if (s<d)
    {
        // start at end of s
        d = d+n-1;
        s = s+n-1;
  
        while (n--)
           *d-- = *s--;
    }
	
    return dest;
}
```

### [LRU的实现](https://leetcode-cn.com/problems/lru-cache/submissions/)

哈希+双链表

```cpp
class LRUCache
{
public:
    struct Node
    {
        int key, val;
        Node *pre, *next;
        Node(int _key, int _val) : key(_key), val(_val), pre(NULL), next(NULL) {}
    } * L, *R;
    unordered_map<int, Node *> hash;
    int n;
    //构造函数，初始化大小和头尾指针
    LRUCache(int capacity)
    {
        n = capacity;
        L = new Node(-1, -1), R = new Node(-1, -1);
        L->next = R, R->pre = L;
    }
    void remove(Node *p)
    {
        p->next->pre = p->pre;
        p->pre->next = p->next;
    }

    void insert(Node *p)
    {
        p->next = L->next;
        p->pre = L;
        L->next->pre = p;
        L->next = p;
    }
    int get(int key)
    {
        if (hash.count(key) == 0)
            return -1;
        auto p = hash[key];
        remove(p);
        insert(p);
        return p->val;
    }
    void put(int key, int value)
    {
        if (hash.count(key))
        {
            auto p = hash[key];
            p->val = value;
            remove(p);
            insert(p);
        }
        else
        {
            if (hash.size() == n)
            {
                auto p = R->pre;
                remove(p);
                hash.erase(p->key);
                delete p;
            }
            auto p = new Node(key, value);
            hash[key] = p;
            insert(p);
        }
    }
};
```



## 操作系统面试题

### 死锁的必要条件、预防死锁、解除死锁

**死锁的四个必要条件**

1. 互斥条件：一个资源每次只能被一个进程使用。
2. 请求和保持条件：一个进程因为请求资源而阻塞时，对已获得的资源保持不放。
3. 不剥夺条件：进程已经获得的资源在没有使用完之前，不能强行剥夺。
4. 循环等待条件：若干进程之间形成一种头尾相接的循环等待资源关系。

解决死锁的基本方法

**预防死锁：**

1）资源一次性分配：一次性分配所有资源，这样就不会有请求了（破坏请求条件）

2）只要有一个资源得不到分配，就不给这也进程分配其他的资源（破坏保持条件）

3）可剥夺资源：即当某进程获得了部分资源，但得不到其它资源，则释放已占有的资源（破坏不剥夺条件）

4）资源有序分配法：系统给每个资源赋予一个编号，每一个进程按照编程递增的顺序请求资源，释放则相反（破坏环路等待条件）

**解除死锁：**

常用的有：

1）剥夺资源：从其他进程剥夺足够数量的资源给死锁进程，以解除死锁状态；

2）撤销进程:可以直接撤销死锁进程或撤销代价最小的进程，直至有足够的资源可用；

### 进程和线程的区别

**进程是资源分配的最小单位，线程是CPU调度的最小单位“**这样的回答感觉太抽象，都不太容易让人理解。

做个简单的比喻：进程=火车，线程=车厢

- 线程在进程下行进（单纯的车厢无法运行）
- 一个进程可以包含多个线程（一辆火车可以有多个车厢）
- 不同进程间数据很难共享（一辆火车上的乘客很难换到另外一辆火车，比如站点换乘）
- 同一进程下不同线程间数据很易共享（A车厢换到B车厢很容易）
- 进程要比线程消耗更多的计算机资源（采用多列火车相比多个车厢更耗资源）
- 进程间不会相互影响，一个线程挂掉将导致整个进程挂掉（一列火车不会影响到另外一列火车，但是如果一列火车上中间的一节车厢着火了，将影响到所有车厢）
- 进程可以拓展到多机，进程最多适合多核（不同火车可以开在多个轨道上，同一火车的车厢不能在行进的不同的轨道上）
- 进程使用的内存地址可以上锁，即一个线程使用某些共享内存时，其他线程必须等它结束，才能使用这一块内存。（比如火车上的洗手间）－"互斥锁"
- 进程使用的内存地址可以限定使用量（比如火车上的餐厅，最多只允许多少人进入，如果满了需要在门口等，等有人出来了才能进去）－“信号量”