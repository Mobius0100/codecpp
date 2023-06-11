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

#include "strBlob.h"

using namespace std;
using line_no = vector<string>::size_type;

class QueryResult;

class TextQuery{
public:
    
    TextQuery(ifstream &in);
    QueryResult query(const string &key) const;
private:
    shared_ptr<StrBlob> file;
    map<string, shared_ptr<set<line_no>>> mp;

};

class QueryResult{
friend ostream& print(ostream&, const QueryResult&);
public:
    QueryResult(string s, 
                shared_ptr<set<line_no>> p,
                shared_ptr<StrBlob> f): sought(s), lines(p), file(f) { };
    set<line_no>::iterator begin();
    set<line_no>::iterator end();
    shared_ptr<StrBlob> get_file();
private:
    string sought;
    shared_ptr<set<line_no>> lines;
    shared_ptr<StrBlob> file;
};