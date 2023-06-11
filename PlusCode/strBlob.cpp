/*
    动态内存与智能指针的使用
    编写一个strblob类，使用shared_ptr进行数据共享
*/
#include "strBlob.h"

using namespace std;

StrBlob::StrBlob(): data(make_shared<vector<string>>()) { }
StrBlob::StrBlob(initializer_list<string> il): data(make_shared<vector<string>>(il)) { }

void StrBlob::check(size_type i, const string &msg) const{
    if(i >= data->size()) throw out_of_range(msg);
}

// const成员函数，表示只读
const string& StrBlob::front() const{
    check(0, "front on empty StrBlob");
    return data->front();
}
const string& StrBlob::back() const{
    check(0, "back on empty StrBlob");
    return data->back();
}

string& StrBlob::front(){
    check(0, "front on empty StrBlob");
    return data->front();
}
string& StrBlob::back(){
    check(0, "back on empty StrBlob");
    return data->back();
}

// pop push 不需要const版本，因为会修改对象的状态
void StrBlob::pop_back(){
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}
////////////////////////////////////////////////////////

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const{
    auto ret = wptr.lock();     //vector是否还存在
    if(!ret) throw runtime_error("unbound StrBlobPtr");
    if(i >= ret->size()) throw out_of_range(msg);
    return ret;
}

string& StrBlobPtr::deref() const{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr(){
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

StrBlobPtr StrBlob::begin(){
    return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end(){
    StrBlobPtr ret = StrBlobPtr(*this, data->size());
    return ret;
}

///////////////////////////////
shared_ptr<vector<string>> ConstStrBlobPtr::check(size_t i, const string &msg) const{
    auto ret = wptr.lock();     //vector是否还存在
    if(!ret) throw runtime_error("unbound StrBlobPtr");
    if(i >= ret->size()) throw out_of_range(msg);
    return ret;
}
ConstStrBlobPtr StrBlob::cbegin() const{ return ConstStrBlobPtr(*this);}
ConstStrBlobPtr StrBlob::cend() const{
    	return ConstStrBlobPtr(*this, data->size());
    }
ConstStrBlobPtr& ConstStrBlobPtr::incr(){
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

string& ConstStrBlobPtr::deref() const {
	auto p = check(curr, "out of range");
	return (*p)[curr];
}