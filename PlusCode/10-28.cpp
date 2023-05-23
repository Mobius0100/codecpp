/*
    再探迭代器：
        ->插入迭代器
        流迭代器
        反向迭代器
        移动迭代器
    
    使用插入迭代器将vec中的元素复制到其他容器中
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
    
int main(){
    vector<int> vec{1,2,3,4,5,6,7,8,9}, vec1, vec2{7,7,7};

    list<int> lst1;

    // front_inserter 添加在容器开头，并且是逆序，因为始终在头部插入
    // front_inserter的对象必须支持push_front
    copy(vec.begin(), vec.end(), front_inserter(lst1));   
    copy(vec.begin(), vec.end(), back_inserter(vec1));    //back_inserter 添加在容器末尾, 必须支持push_back
    copy(vec.begin(), vec.end(), inserter(vec2, vec2.begin() + 1));  // inserter 可以指定插入位置

    cout << "front_inserter: " << endl;
    for(auto num : lst1){
        cout << num << " ";
    }

    cout << endl << "back_inserter: " << endl;
    for(auto num : vec1){
        cout << num << " ";
    }

    cout << endl << "inserter: " << endl;
    for(auto num : vec2){
        cout << num << " ";
    }
    cout << endl;

    return 0;
}