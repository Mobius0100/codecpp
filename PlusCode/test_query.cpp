/*
    
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "text_query_ans.h"

using namespace std;

void runQueries(ifstream &infile){
    TextQuery tq(infile);
    while(true){
        cout << " Enter word to look for, or q to quit: ";
        string s;
        if(!(cin >> s) || s == "q") break;

        print(cout, tq.query(s)) << endl;
    }
}

int main(){
    ifstream input("/Users/lucifer/Project/codecpp/PlusCode/data/Loneliness and Wind.txt");
    runQueries(input);
    
    return 0;
}