/*
    定义一个作者以及其作品的multimap，使用find在multimap中查找一个元素并erase删除。确保程序在元素不在map中时也能正常运行
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <map>

using namespace std;
    
int main(){
    multimap<string, string> mp;

    mp.insert({"Jack", "<my loving path>"});
    mp.insert({"Jack", "<my loving path - 2>"});
    mp.insert({"Tom", "<Death to live>"});
    mp.insert({"Tom", "<Live to Death>"});
    mp.insert({"Alin", "<oh my love>"});

    string author = "Jack";
    string book = "<my loving path>";

    auto range = mp.equal_range(author);
    auto it = find_if(range.first, range.second, [&](const pair<string, string>& pair) {
        return pair.second == book;
    });

    if(it != range.second){
        mp.erase(it);
        cout << "find and erase" << endl;
    }else{
        cout << "not found" << endl;
    }

    for(auto &i : mp){
        cout << i.first << " --- " << i.second << endl;
    }
    
    return 0;
}