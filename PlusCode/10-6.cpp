/*
    使用fill_n、fill
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
    
int main(){
    vector<int> vec(10, 0);
    vector<int> vec2;
    
    // reserve只预留空间，并没有实际改变vector大小，需要使用resize调整大小
    // vec2.reserve(10);
    vec2.resize(10);

    // 迭代器范围、值
    fill(vec.begin(), vec.end(), 1);

    for(auto num : vec){
        cout << num << " ";
    }

    // 单迭代器、计数值、值
    fill_n(vec2.begin(), 10, 7);

    for(auto num : vec2){
        cout << num << " ";
    }
    
    
    return 0;
}