/*
    使用accumulate计算元素和;
    使用equal比较的注意事项
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <numeric>

using namespace std;
    
int main(){
    vector<double> v(5,7.0);
    string str1 = "links", str2 = "links";
    char str3[] = {'a', 'b', 'c'};
    char *str4 = "mipha";

    // equal假定比较的两个元素长度相等，否则只比较第一个序列的长度
    cout << equal(str1.cbegin(), str1.cend(), str2.begin()) << endl;

    // 必须能够使用+运算符，且类型能够转换
    int sum = accumulate(v.cbegin(), v.cend(), 0);

    cout << sum << endl;
    
    return 0;
}