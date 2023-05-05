#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
 
using namespace std;
    
int main(){
    vector<int> vec1;  //使用默认构造函数创建vec, 其中不包含任何值
    vector<int> vec2(5, 7);    //创建5个默认值为7的vec, 默认值可以不指定
    vector<int> vec3(vec2);    //使用拷贝构造函数创建vec，值和vec2一样
    vector<int> vec4 = {1, 2, 3, 4, 5};   
    vector<int> vec5{1, 2, 3, 4, 5};       //使用初始化列表进行初始化容器，vec4也是一样
    vector<int> vec6(vec5.begin() + 1, vec5.end() - 1);   //使用迭代器初始化vec

    
    return 0;
}