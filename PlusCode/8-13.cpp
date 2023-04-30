#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

struct PersonInfo{
    string name;
    vector<string> phones;
};

int main(){
    ifstream input("./data/8-13.txt");

    string line, word;
    vector<PersonInfo> people;

    while(getline(input, line)){
        PersonInfo info;
        istringstream record(line);
        record >> info.name;
        while(record >> word){
            info.phones.push_back(word);
        }
        people.push_back(info);
    }
    
    return 0;
}