/*
    
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
 
using namespace std;
    
int main(){
    vector<string> vec;
    string word;

    auto iter = vec.begin();
    while(cin >> word){
        iter = vec.insert(iter, word);
    }

    for(auto str : vec){
        cout << str << " ";
    }
    
    return 0;
}