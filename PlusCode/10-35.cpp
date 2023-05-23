/*
    反向迭代器的使用
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
    
int main(){
    ostream_iterator<int> out_it(cout, " ");

    vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    copy(vec.begin(), vec.end(), out_it);
    cout << endl;
    copy(vec.rbegin(), vec.rend(), out_it);


    
    return 0;
}