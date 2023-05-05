#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
 
using namespace std;

//注意传入的是引用
std::vector<int>::iterator find(vector<int> &nums, int value){
    for(auto it=nums.begin(); it != nums.end(); ++it){
        if(*it == value) return it;
    }

    return nums.end();
}

int main(){
    vector<int> vec = {1, 2, 3, 4, 5};
    auto it = find(vec, 6);

    if (it != vec.end()) {
        std::cout << "Found " << *it << std::endl;
    }else {
        std::cout << "Not found" << std::endl;
    }
    return 0;
}