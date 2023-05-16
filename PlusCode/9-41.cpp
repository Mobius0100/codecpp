/*
    从一个vector<char>中初始化一个string
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
    
int main(){
    vector<char> source {'a', 'b', 'c', 'd', 'e', 'm', 'i', 'p'};
    vector<int> nums {1, 2, 3, 4, 5};

    string str(source.begin(), source.end());
    string num(nums.begin(), nums.end());

    cout << num << endl;
    
    return 0;
}