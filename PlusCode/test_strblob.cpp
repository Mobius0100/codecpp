/*
    test for strblob
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <queue>
#include <set>
#include <fstream>
#include "strBlob.h"

using namespace std;

int main(){
    StrBlob str = {"string", "vector", "list"};
    StrBlobPtr ptr = str.begin();
    int size = str.size();
    while(size--){
        cout << ptr.deref() << endl;
        ptr.incr();
    }

    return 0;
}