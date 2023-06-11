/*
    Point是一个类，以下代码哪里用到了拷贝构造函数？

    拷贝构造函数发生的条件：
        1. 使用=定义变量时
        2. 将一个对象作为实参传递给一个非引用类型的形参
        3. 从一个返回类型为非引用类型的函数返回一个对象
        4. 用花括号列表初始化一个数组中的元素或一个聚合类中的成员
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
    
Point global;
Point foo_bar(Point arg){     // 2
    Point local = arg, *heap = new Point(global);   // 1
    *heap = local;
    Point pa[4] = {local, *heap};  // 1
    return *heap;   //3
}