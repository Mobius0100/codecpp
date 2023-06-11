/*
    测试vector
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
    
int main(){
    vector<int> vec1 {0, 1, 2, 3};
    int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    int len = sizeof(ia) / sizeof(ia[0]);
    vector<int> vec2(ia, ia+len);
    list<int> lst1(ia, ia+len);

    cout << vec1.front() << endl;
    cout << *vec1.begin() << endl;
    // cout << vec2.front() << endl;
    // cout << vec2.at(0) << endl;

    auto iterv = vec2.begin();
    auto iterl = lst1.begin();

    while(iterv != vec2.end()){
        if(*iterv % 2 == 0){
            iterv = vec2.erase(iterv);
        }else{
            ++iterv;
        }
    }

    while(iterl != lst1.end()){
        if(*iterl % 2 != 0){
            iterl = lst1.erase(iterl);
        }else{
            ++iterl;
        }
    }
    cout << "List: "; 
    for(auto num : lst1){
        cout << num << " ";
    }
    cout << endl << "Vector: ";

    for(auto num : vec2){
        cout << num << " ";
    }

    return 0;
}   