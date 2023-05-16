/*
    
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
    
int main(){
    vector<string> svec;
    svec.reserve(10);
    string word;
    while(cin >> word) svec.push_back(word);
    svec.resize(svec.size() + svec.size() / 2);
    
    cout << svec.size() << " " << svec.capacity() << endl;

    for(auto wrd : svec){
        cout << wrd << "#";
    }

    return 0;
}