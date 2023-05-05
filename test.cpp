#include <iostream>

using namespace std;

int main() {
    int num = 10;
    int k = 1;

    // 定义引用
    int &ref = num;

    // 输出引用的值
    cout << "ref: " << ref << endl;

    // 修改引用所绑定的值
    ref = k;

    // 再次输出引用的值
    cout << "ref: " << num << endl;

    return 0;
}