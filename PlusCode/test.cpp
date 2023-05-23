/*
    test
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <queue>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <set>

using namespace std;
    
int main(){
    multiset<string> c;
    vector<string> v{"link", "love", "mipha"};

    // copy(v.begin(), v.end(), back_inserter(c));   error
    copy(v.begin(), v.end(), inserter(c, c.end()));

    copy(c.begin(), c.end(), back_inserter(v));
    copy(c.begin(), c.end(), inserter(v, v.end()));


    for(auto &s : c){
        cout << s << " ";
    }
    cout << endl;

    for(auto &s : v){
        cout << s << " ";
    }

    return 0;
}