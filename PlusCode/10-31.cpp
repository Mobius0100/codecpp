/*
    使用流迭代器从标准输入读取整数序列，排序去重后将结果写到标准输出
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <fstream>

using namespace std;
    
int main(){
    istream_iterator<int> in_it(cin), eof;
    //ostream_iterator<T> out(os, d) out将类型为T的值写到输出流os中，每个值后面都输出一个d，d指向一个以空字符结尾的字符数组
    ostream_iterator<int> out_it(cout, "->");
    vector<int> num;

    // copy第三个参数接受一个输出迭代器
    copy(in_it, eof, back_inserter(num));

    sort(num.begin(), num.end());

    // 用erase 和unique去重
    // num.erase(unique(num.begin(), num.end()), num.end());

    // 将num中的元素去重后直接打印出来
    unique_copy(num.begin(), num.end(), out_it);    
    
    return 0;
}