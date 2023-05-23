/*
    再探迭代器：
        插入迭代器
        ->流迭代器
        反向迭代器
        移动迭代器
        
    使用流迭代器读取文件，存入vector string中
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <fstream>

using namespace std;
    
int main(){
    ifstream input_file("/Users/lucifer/Project/CppCode/PlusCode/data/Loneliness and Wind.txt");
    
    // <>中为需要读写的数据类型，input_file为绑定对象
    istream_iterator<string> infile_it(input_file);
    istream_iterator<string> eof;

    vector<string> result;

    // 方法一：循环
    // while(infile_it != eof){
    //     result.push_back(*infile_it++);
    // }

    // 方法二：copy
    copy(infile_it, eof, back_inserter(result));

    for(auto str : result){
        cout << str << " ->" << endl;
    }

    
    return 0;
}