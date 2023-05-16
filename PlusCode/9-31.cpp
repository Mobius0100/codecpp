/*
    改变容器的循环，在容器中添加和删除对迭代器的影响
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
    
int main(){
    vector<int> vi(10, 7);
    list<int> li = {1, 2, 11, 4, 5, 6, 7, 8, 9};
    auto iter_l = li.begin();
    auto iter = vi.begin();

    vi.reserve(1024);

    cout << vi.capacity() << endl;

    while(iter_l != li.end()){
        if(*iter_l % 2){
            iter_l = li.insert(iter_l, *iter_l);
            iter_l++;
            iter_l++;
        }else{
            iter_l = li.erase(iter_l);
        }
    }

    //删除偶数元素，复制奇数元素
    // while(iter != vi.end()){
    //     if(*iter % 2){
    //         //insert在给定位置之前插入新元素,返回指向新元素的迭代器
    //         iter = vi.insert(iter, *iter);
    //         iter += 2;
    //     }else{
    //         iter = vi.erase(iter);
    //         //erase后返回的迭代器指向序列中下一个元素
    //     }
    // }

    //vector插入后不修改iter会怎样？
    // while(iter != vi.end()){
    //     ++iter;
    //     // insert后，插入位置之后的元素迭代器失效，若不将insert返回的迭代器指向iter，该iter会失效
    //     iter = vi.insert(iter, 42);
    //     ++iter;
    // }
    
    for(auto num : vi){
        cout << num << " ";
    }
    return 0;
}