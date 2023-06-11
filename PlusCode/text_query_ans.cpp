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
#include "text_query_ans.h"

using namespace std;
using line_no = vector<string>::size_type;

TextQuery::TextQuery(ifstream &in): file(new StrBlob){
    string text;
    while(getline(in, text)){
        file->push_back(text);
        int nu = file->size() - 1;
        istringstream line(text);
        string word;
        while(line >> word){
            auto &str = mp[word];
            if(!str) str.reset(new set<line_no>);
            str->insert(nu);
        }
    }
}

QueryResult TextQuery::query(const string &key) const{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);

    auto loc = mp.find(key);
    if(loc == mp.end()) return QueryResult(key, nodata, file);
    else return QueryResult(key, loc->second, file);
}

ostream &print(ostream &os, const QueryResult &qr){
    os << qr.sought << " occurs " << qr.lines->size() << " time" << endl;

    auto beg = qr.file->begin();
    for(auto num : *qr.lines){
        auto iter = qr.file->begin();
        auto line_nu = num;
        while(--line_nu){
            iter.incr();
        }
        os << "\t(line " << num + 1 << ") " << iter.deref() << endl;
        // os << "\t(line " << num + 1 << ") " << qr.file->begin().incr() << endl;
    }

    return os;
}

set<line_no>::iterator QueryResult::begin(){
    return lines->begin();
}

set<line_no>::iterator QueryResult::end(){
    return lines->end();
}

shared_ptr<StrBlob> QueryResult::get_file(){
    return file;
}
