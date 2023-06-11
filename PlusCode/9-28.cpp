/*
    查找list中第一个string，将第二个string插入到第一个string后
    找不到则插入到末尾
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <forward_list>

using namespace std;

void func(forward_list<string> &lst, string str1, string str2){
    // 首前迭代器
    auto prev = lst.before_begin();
    auto cur = lst.begin();

    while(cur != lst.end()){
        if(*cur == str1){
            break;
        }
        prev = cur;
        ++cur;
    }

    //在prev的后一位插入str2
    if(cur == lst.end()){
        lst.insert_after(prev, str2);
    }else{
        lst.insert_after(cur, str2);
    }

}

int main(){
    forward_list<string> lst {"Mipha", "Link", "Zelda", "Legend"};

    func(lst, "Me", "Love");

    for(auto str : lst){
        cout << str << " ";
    }
    
    return 0;
}