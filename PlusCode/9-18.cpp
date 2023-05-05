/*
    读取string，存入deque，打印 
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;
    
int main(){
    string str;
    deque<string> deq;

    while(cin >> str){
        deq.push_back(str);
    }

    for(auto it=deq.rbegin(); it != deq.rend(); ++it){
        cout << *it << endl;
    }

    
    return 0;
}       