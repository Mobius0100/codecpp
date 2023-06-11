/*
    map :
        find(), count()
        upper_bound(), lower_bound(), equal_range()
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <map>

using namespace std;
    
int main(){
    map<string, vector<int>> mp{{"link", vector<int>{1,2}}, {"mipha", {1,2}}};

    auto it = mp.find("mipha");

    auto up = mp.upper_bound("zelda");  // 若关键字不在容器中，up、low都将指向关键字正确的插入位置，两个迭代器形成一个空范围。  
    map<string, vector<int> >::iterator low = mp.lower_bound("mipha");

    cout << it->first << endl;
    // cout << up << endl;
    cout << low->first << endl;
   
    return 0;
}