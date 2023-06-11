/*
    编写函数，返回一个动态分配的int的vector.将此vector传递给另一个函数，这个函数读取标准输入，将读入的值保存在vector元素中。再将vector传递给另一个函数，打印读入的值。记得在恰当位置delete vector
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

vector<int>* create(){
    vector<int> *vec = new vector<int>();
    return vec;
}    

vector<int>* read(vector<int> *vec){
    int num;
    while(cin >> num){
        vec->push_back(num);
    }

    return vec;
}

void print_out(vector<int> *vec){
    for(auto num : *vec){
        cout << num << "-";
    }
    cout << endl;
    delete vec;
}

int main(){
    auto vec = create();
    vec = read(vec);
    print_out(vec);
    
    return 0;
}