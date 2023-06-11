/*
    
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include<time.h>

using namespace std;

class numbered{
public:
    numbered() {mysn = idx++;}
    numbered(const numbered& ori){mysn = ori.mysn; mysn++;}
    static int idx;
    int mysn;
};

int numbered::idx = 0;

void func(numbered s){
    cout << s.mysn << endl;
}
void func2(const numbered &s){
    cout << s.mysn << endl;
}

int main(){
    // srand(time(0));
    numbered a;
    func(a);
    
    return 0;
}