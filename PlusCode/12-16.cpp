/*
    unique_ptr的使用
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

struct destination;
struct connection;

int main(){
    unique_ptr<string> p;
    unique_ptr<string> p2(p);
    
    return 0;
}