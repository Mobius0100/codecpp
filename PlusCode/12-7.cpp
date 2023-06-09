/*
    编写函数，返回一个动态分配的int的vector.将此vector传递给另一个函数，这个函数读取标准输入，将读入的值保存在vector元素中。再将vector传递给另一个函数，打印读入的值。记得在恰当位置delete vector
    使用shared_ptr
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <memory>

using namespace std;

typedef shared_ptr<vector<int>> vi_ptr;

shared_ptr<vector<int>> create(){
    shared_ptr<vector<int>> v = make_shared<vector<int>>();
    return v;                   
}    

vi_ptr read(vi_ptr vec){
    int num;
    while(cin >> num){
        vec->push_back(num);
    }

    return vec;
}

void print_out(vi_ptr vec){
    for(auto num : *vec){
        cout << num << "-";
    }
    cout << endl;
}

int main(){
    auto vec = create();
    vec = read(vec);
    print_out(vec);
    
    return 0;
}