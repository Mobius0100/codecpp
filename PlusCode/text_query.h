/*
    12-27
    TextQuery类的定义
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;
class QueryResult;

class TextQuery{
public:
    TextQuery(ifstream in){
        string line;
        while(getline(in, line)){
            text.push_back(line);
        }

        for(int i=0; i<text.size()-1; ++i){
            istringstream lines(text[i]);
            string word;
            while(lines >> word){
                // mp插入？
                mp[word].insert(i+1);
            }
        }
    }
    QueryResult query(string key);
private:
    vector<string> text;
    map<string, set<int>> mp;

};

class QueryResult{
public:
    QueryResult();
private:
    shared_ptr<vector<string>> 
}
