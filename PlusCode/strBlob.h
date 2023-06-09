/*
    动态内存与智能指针的使用
    编写一个strblob类，使用shared_ptr进行数据共享
*/
#ifndef STRBLOB_H
#define STRBLOB_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
class StrBlobPtr;
class ConstStrBlobPtr;

class StrBlob{
    friend class StrBlobPtr;
    friend class ConstStrBlobPtr;
public:
    //vector<string>::size_type是类模板中定义的一个公共成员类型，用于表示容器中元素的数量或索引的类型。
    //它是一个无符号整数类型，通常被用作索引或循环变量，以确保正确地访问容器的元素。
    //使用 vector<string>::size_type 而不是具体的整数类型，可以增强代码的可移植性和通用性，
    //因为 size_type 类型的具体实现可能因编译器和平台而异。使用该类型可以确保在不同平台上的一致性，并避免与特定整数类型相关的问题。
    typedef vector<string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    /*
    12.5 : 使用explicit：
    优点：
        方便性：允许使用隐式转换，可以使代码更简洁，不需要显式地调用构造函数来创建对象。
        语义上的合理性：如果将一个 string 对象作为参数，构造函数可以合理地将其转换为类对象，从而增强了代码的可读性和可理解性。
    缺点：
        意外的隐式转换：隐式转换可能会导致意外的行为，特别是在函数重载的情况下，可能会导致不符合预期的函数调用。
        可能引发歧义：如果存在多个具有相同参数类型的构造函数，允许隐式转换可能会导致编译器无法确定调用哪个构造函数，从而产生二义性。
    */

    size_type size() const { return data->size(); }
    void push_back(const string &t) { data->push_back(t); }
    void pop_back();
    const string& front() const;
    const string& back() const;
    string& front();
    string& back();

    StrBlobPtr begin();
    StrBlobPtr end();
	ConstStrBlobPtr cbegin() const;
	ConstStrBlobPtr cend() const;
private:
    shared_ptr<vector<string>> data;
    void check(size_type i, const std::string &msg) const;
};

/////////////////////////////////////    
class StrBlobPtr{
public:
    StrBlobPtr(): curr(0) { }
    StrBlobPtr(StrBlob &a, size_t sz = 0): wptr(a.data), curr(sz) { }
    string& deref() const;
    StrBlobPtr& incr();
private:
    shared_ptr<vector<string>> check(size_t, const string&) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

/// 12-22题 //////////////////////////
class ConstStrBlobPtr{
public:
	ConstStrBlobPtr():curr(0){}
	ConstStrBlobPtr(const StrBlob& a, size_t sz = 0): wptr(a.data), curr(sz){}
	string& deref() const;
	ConstStrBlobPtr& incr();
 
private:
	weak_ptr<vector<string>> wptr;
	size_t curr;
	shared_ptr<vector<string>> check(size_t index, const string& msg) const;
};

#endif  