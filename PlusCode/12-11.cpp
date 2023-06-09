/*
    智能指针shared_ptr的一些使用注意事项
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

void process(shared_ptr<int> ptr){
    // 使用ptr
}

int main(){
    shared_ptr<int> p(new int(42));
    process(shared_ptr<int>(p));  // 正确， 调用拷贝构造函数，引用次数加一，当该语句执行完，临时指针析构，引用次数减一，不为0，正常运行。
    process(shared_ptr<int>(p.get()));    
    //错误， p.get()返回一个内置指针，使用其初始化一个智能指针，导致该临时智能指针和原始p指向同一内存，但引用次数各自独立。
    //因此，该语句执行完后，临时指针析构，内存被释放。导致原始p悬空

    auto p1 = new int();
    auto sp = make_shared<int>();

    process(sp);   //正确，传入sp
    process(new int());  //错误，传入的值不是智能指针，类型不匹配，且智能指针的构造函数是explicit的，不能进行隐式转换。
    process(p1);   //错误，同上
    process(shared_ptr<int>(p1));  //合法，但当利用内置指针直接初始化临时变量的智能指针ptr，当process函数结束时，ptr指针析构，内存空间释放，所以内置指针p1变为空悬指针，不能使用。

    auto p2 = sp.get();   // p2是一个内置指针， int*
    delete p2;    //错误，p2指向的内存是右shared_ptr管理，不应该手动删除，可能会导致资源的重复释放，或者使用已释放的内存，导致未定义的行为。从而导致程序崩溃等结果

    return 0;
}