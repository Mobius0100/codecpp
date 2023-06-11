/*
    allocator的使用
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <memory>

using namespace std;
    
int main(){
    allocator<string> alloc;
    size_t size = 10;
    auto const begin = alloc.allocate(size);
    auto curr = begin;
    string s;

    while(cin >> s && curr != begin + size) alloc.construct(curr++, s);
    while(curr != begin){
        cout << *--curr << endl;
        alloc.destroy(curr);
    }    
    
    alloc.deallocate(begin, size);
    
    return 0;
}