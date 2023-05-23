/*
    接受三个参数：一个输入文件、两个输出文件的文件名；
    输入文件保存的是整数

    使用istream_iterator读取，ostream——iterator奇数写入第一个输出文件，值后+空格；偶数写入第二个输出文件，值后换行
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <fstream>

using namespace std;
    
int main(){
    string file1 = "./data/10-33.txt";
    string file2 = "./data/10-33_out1.txt";
    string file3 = "./data/10-33_out2.txt";

    ifstream infile(file1);
    ofstream outfile1(file2), outfile2(file3);

    istream_iterator<int> in_it(infile);
    istream_iterator<int> eof;
    ostream_iterator<int> out_it1(outfile1, " "), out_it2(outfile2, "\n");

    while(in_it != eof){
        int value = *in_it;

        if(value % 2 == 0) *out_it2++ = value;
        else *out_it1++ = value;
        ++in_it;
    }
   
    
    return 0;
}