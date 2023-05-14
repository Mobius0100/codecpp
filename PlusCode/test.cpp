/*
    test
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <queue>

using namespace std;
    
int main(){
    int a[5] = {1, 2, 3, 4, 5};
    priority_queue<int> pq(a, a+5);

    vector<int> v = {1, 2, 3, 4, 5};
    queue<int> q(a, a+5);

    
    return 0;
}