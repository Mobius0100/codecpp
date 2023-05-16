/*
    统计int序列中有多少元素等于给定值
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
    
int main(){
    vector<int> nums;
    list<string> lst;
    string str;
    int n;

    while(cin >> str){
       lst.push_back(str); 
    }

    int cnt = count(lst.begin(), lst.end(), "mipha");

    cout << cnt << endl;
    
    return 0;
}