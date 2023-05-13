/*
    
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
    
int main(){
    vector<int> vec(100,7);

    cout << vec.capacity() << endl;

    vec.push_back(9);

    cout << vec.capacity() << endl;
    
    return 0;
}