/*
    定义map，key是家庭的姓，value是vector，保存孩子们的名。
    实现添加新的家庭以及向已有家庭中添加孩子
    # 关于字符串的分割 # 
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <sstream>

using namespace std;

map<string, vector<string>> mp;

// 使用find和substr进行分割
vector<string> split(const string &str, char sp){
    vector<string> token;
    size_t start = 0;
    size_t end = str.find(sp);

    while(end != string::npos){
        token.push_back(str.substr(start, (end-start)));
        start = end + 1;
        end = str.find(sp, start);
    }

    string lastToken = str.substr(start);
    token.push_back(lastToken);

    return token;
}

// 使用stringstream分割，包含在sstream头文件中
vector<string> split_s(const string &str, char sp){
    vector<string> tokens;
    string token;
    std::istringstream tokenStream(str);

    while(getline(tokenStream, token, sp)){
        tokens.push_back(token);
    }

    return tokens;
}

// input ： family xing child name1 name2 ...

int main(){
    ostream_iterator<string> out_it(cout, " ");
    string input;
    // 读取包含空格的字符串
    while(getline(cin, input)){
        vector<string> word;
        word = split_s(input, ' ');   //按空格进行分割

        string family = word[1];
        for(int i=3; i<word.size(); i++){
            mp[family].push_back(word[i]);
        }
    }

    //迭代map进行输出
    for(auto &f : mp){
        cout << f.first << ": ";
        copy(f.second.begin(), f.second.end(), out_it);
        cout << endl;
    }


    return 0;
}