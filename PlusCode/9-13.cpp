#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <typeinfo>
 
using namespace std;
    
int main(){
    list<int> lst1 = {1, 2, 3, 4, 5};
    vector<int> vec0{6, 7, 8, 9, 10};

    // vector<double> vec1(lst1.begin(), lst1.end());
    vector<double> vec1;
    vec1.assign(lst1.begin(), lst1.end());        //使用assign进行赋值
    // vector<double> vec2(vec0);  //创建一个容器为另一个容器的拷贝时，容器类型和元素类型必须完全匹配，否则使用迭代器进行范围拷贝
    vector<double> vec2(vec0.cbegin(), vec0.cend());

    for(auto num : vec1){
        cout << num << typeid(num).name() << endl;
    }

    cout << endl;
    for(const auto &elem : vec2){
        cout << elem << typeid(elem).name() << endl;
    }

    return 0;
}