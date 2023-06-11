/*
    定义一个使用引用计数的类，共享数据但不使用shared_ptr
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

class HasPtr{
private:
    string *ps;
    int *use;   // 新建一个引用计数的指针指向一块动态内存，用于记录有多少个对象在引用
public:
    HasPtr(const string &str):ps(new string(str)), use(new int(1)) { }
    HasPtr(const HasPtr &ori):ps(ori.ps), use(ori.use){
        ++*use;
    }
    HasPtr& operator=(const HasPtr &other){
        ++*other.use;
        if(--*use == 0){
            delete ps;
            delete use;
        }
        ps = other.ps;
        use = other.use;

        return *this;
    }
    ~HasPtr(){
        if(--*use == 0){
            delete ps;
            delete use;
        }
    }
    
    void print(){
        cout << *ps << *use << endl;
    }
};

int main(){
    HasPtr s1("Link");
    HasPtr s2 = s1;
    HasPtr s3("Mipha");

    s1.print(), s2.print(), s3.print();
    cout << "s3=s1" << endl;
    s3 = s1;
    s1.print(), s2.print(), s3.print();

    return 0;
}