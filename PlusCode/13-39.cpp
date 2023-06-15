/*
    编写一个简化的vector，不用模版，只针对string StrVec
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <memory>
#include <utility> //move

using namespace std;

class StrVec{
public:
    StrVec():elements(nullptr),first_free(nullptr),cap(nullptr){}
    StrVec(const StrVec &);
    StrVec(StrVec &&) noexcept;
    StrVec &operator=(const StrVec &&);
    StrVec &operator=(const StrVec &);
    ~StrVec();
    void push_back(const string &);
    size_t size() const {return first_free-elements;}
    size_t capacity() const {return cap-elements;}
    string *begin() const {return elements;}
    string *end() const {return first_free;}

private:
    static allocator<string> alloc; 
    string *elements;
    string *first_free;
    string *cap;

    pair<string*, string*> alloc_n_copy(const string*, const string*);
    void chk_n_alloc(){
        if(size()==capacity()) reallocate();
    }
    void reallocate();
    void free();
};

StrVec::StrVec(const StrVec &other){
    //分配other元素一样多的空间
    auto newdata = alloc_n_copy(other.begin(), other.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::StrVec(StrVec &&other) noexcept : elements(other.elements), first_free(other.first_free), cap(other.cap){
    other.elements = other.first_free = other.cap = nullptr;
}

StrVec&
StrVec::operator=(StrVec &&rhs){
    
}

StrVec::~StrVec(){
    free();
}

void StrVec::push_back(const string& s){
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

pair<string*, string*>
StrVec::alloc_n_copy(const string *b, const string *e){
    auto data = alloc.allocate(e-b);
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free(){
    if(elements){
        for(auto p = first_free; p != elements;){
            alloc.destroy(--p);
        }
        alloc.deallocate(elements, cap-elements);
    }
}

void StrVec::reallocate(){
    //分配两倍内存或者当strvec为空时分配一个元素空间
    auto new_capacity = size() ? 2 * size() : 1;
    //分配新内存
    auto new_data = alloc.allocate(new_capacity);
    // 将数据从旧内存移动到新内存
    auto dest = new_data;
    auto elem = elements;
    for(size_t i = 0; i != size(); ++i){
        alloc.construct(dest++, std::move(*elem++));
    }
    free();
    elements = new_data;
    first_free = dest;
    cap = elements + new_capacity;

}