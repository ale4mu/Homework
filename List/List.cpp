#include "List.h"
#include <iostream>
#include<vector>

template<typename T>
void printlist(const List<T>& list)//printlist函数方便后续测试
{   
    if(list.empty())
        std::cout << "empty list" << std::endl;
    else
    {
    for(const auto& i:list)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    }
}

int main()
{
    List<int> list1;//测试默认构造函数 List()
    std::cout << "this is list1:";
    printlist(list1);

    List<int> list2={1,3,5,7,9};//测试初始化列表构造函数List(std::initializer_list<Object> il)
    std::cout << "this is list2:";
    printlist(list2);

    List<int> list3(list2);//测试拷贝构造函数List(const List &rhs)
    std::cout << "this is list3:";
    printlist(list3);

    List<int> list4;//测试赋值运算符List &operator=(List copy)
    list4=list2;
    std::cout << "this is list4:";
    printlist(list4);
  


    
    List<int> list5(std::move(list3));//测试移动构造函数List(List &&rhs)
    std::cout << "this is list5:";
    printlist(list5);
    printlist(list3);//list3应为空

    std::cout << "size of list5:" << list5.size() << std::endl;//测试size()函数
    if(list3.empty())//测试empty()函数
        std::cout << "list3 is empty" << std::endl;
    if(!(list5.empty()))
        std::cout << "list5 is not empty" << std::endl;

    

    //front()函数和back()函数需要测试吗？？
    int front=list5.front();
    int back=list5.back();
    std::cout << "this is front:" << front << std::endl;
    std::cout << "this is back:" << back << std::endl;



    int a=10;//测试在头部插入函数push_front(左值版本和右值版本)
    list5.push_front(std::move(a));
    list5.push_front(10);
    std::cout << "this is list5 after push_front:";
    printlist(list5);
   
    list5.push_back(std::move(a));//测试在尾部插入函数push_back(左值版本和右值版本)
    list5.push_back(10);
    std::cout << "this is list5 after push_back:";
    printlist(list5);
    
    list5.pop_front();//测试pop_front()
    std::cout << "this is list5 after pop_front:";
    printlist(list5);
    list5.pop_back();//测试pop_back()
    std::cout << "this is list5 after pop_back:";
    printlist(list5);

   
    int b=6;
    list5.insert(++list5.begin(),8);//测试insert()函数(左值版本和右值版本)
    std::cout << "this is list5 after insert8:";
    printlist(list5);
    list5.insert(++list5.begin(),std::move(b));
    std::cout << "this is list5 after insert6:";
    printlist(list5);
   
    // list3.insert(list3.begin(),8);//空链表插入报错
    // std::cout << "this is list3 after insert8:";
    // printlist(list3);

    // list3.push_front(8);//push_front(8)=insert(listt3.begin(),8)因此也会报错
//     std::cout << "this is list3 after push_front 8:";
//     printlist(list3);

    // list1.push_back(8);//空链表push_back(8)报错
    // std::cout << "this is list3 after push_back 8:";
    // printlist(list1);

    // list1.pop_front();//空链表pop_front()报错
    // std::cout << "this is list3 after pop_front:";
    // printlist(list1);
    // list1.pop_back();//空链表pop_back()报错
    // std::cout << "this is list3 after pop_back:";
    // printlist(list1);

    list5.erase(++list5.begin());//测试erase(iterator itr)删除指定节点
    std::cout << "this is list5 after erase:";
    printlist(list5);
    list5.erase(++list5.begin(),--list5.end());//测试erase(iterator from, iterator to)删除范围节点
    std::cout << "this is list5 after erase:";
    printlist(list5);



    //测试深度复制
    list2.pop_front();
    std::cout << "this is list2 after pop_front:" ;
    printlist(list2);
     std::cout << "this is list4 after pop_front list2:" ;
    printlist(list4);

    //测试连续复制
    List<int> list6;
    list6=list3=list2;
    std::cout << "this is list3:" ;
    printlist(list3);
    std::cout << "this is list6:" ;
    printlist(list6);

    list4.clear();//测试clear()函数
    std::cout << "this is list4:";
    printlist(list4);
    // list5.erase(list5->head,list5->tail);
    // printlist(list5);




    



// Chicken a= c;
// print(a); // 测试【赋值构造函数】是否正确，能正确输出给 20 分
// c.setName("Xukun Cai");
// print(c);
// print(a);
// print(d); // 测试是否为【深度复制】，本行与上两行能正确输出给 20 分
// Chicken b;
// b = d = c;
// print(b);
// print(d); // 测试【连续赋值】功能，本行与上一行能正确输出给 20 分
    


//    for (int i = 0; i < 10; ++i)
//     {
//         lst.push_back(i);
//     }

    // lst.pop_back();

    return 0;
}
