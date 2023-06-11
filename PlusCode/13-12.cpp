/*
    理解拷贝控制成员和构造函数，定义一个类，并打印出名字    
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
    
class X{
public:
    X() {cout << "默认构造函数：X()" << endl;}
    X(int i): v(i){
        cout << "自定义构造函数X(int i), value:" << v << endl;
    }

    X(const X&) {
        cout << "拷贝构造函数：X(const X&)" << endl;
    }
    X& operator=(const X &ori){
        cout << "拷贝赋值运算符：operator=(const X &ori)" << endl;
        return *this;
    }
    ~X(){
        cout << "析构函数：~X()" << endl;
    }
private:
    int v;
};

void func(X class1, X &class2, X *class3){
    vector<X> vec1{class1, class2, *class3};

}

void reference(X&) {  };
void unreference(X) {  };

int main(){

    X x1;
    X x2 = x1;
    X x3(x2);
    X * x4 = new X(7);
    // X * x5 = new X(x1);
    x2 = x1;
    vector<X> x6;
    // vector<X> x7{x2};
    // cout << "push进容器" <<endl;
    // x6.push_back(x1);
    cout << "引用传值  " << endl;
    reference(x1);  
    cout << "非引用传值" << endl;
    unreference(x1);
    cout << "删除x4" << endl;
    delete x4;
    // cout << "删除x5" << endl;
    // delete x5;
    cout << "程序结束" << endl;

    return 0;
}       