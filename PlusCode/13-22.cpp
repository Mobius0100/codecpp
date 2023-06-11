/*
    实现一个类，使其行为像一个值，即不共享状态，有两个成员，一个int和一个string指针。
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

class HasPtr{
public:
    HasPtr(){
        value = 0;
        str = new string();
    };
    HasPtr(const string &s):str(new string(s)), value(1){ }
    HasPtr(const HasPtr & ori):value(ori.value), str(new string(*(ori.str))){}
    HasPtr& operator=(const HasPtr& other){
        if(this != &other){
            value = other.value;
            *str = *(other.str);
        }
        return *this;
    }
    void print(){
        cout << *str << "---" << value << endl;
    }
private:
    int value;
    string *str;
};
int main(){
    HasPtr test1("Link"), test2("Mipha"), test3 = test1;
    cout << "test3 ori:";
    test3.print();

    test3 = test2;
    cout << "test1:";
    test1.print();
    cout << "test2:";
    test2.print();
    cout << "test3 = after:";
    test3.print();
    
    return 0;
}