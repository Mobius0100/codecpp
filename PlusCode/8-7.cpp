/*
    以文件形式读取销售记录并输出。
*/
#include <iostream>
#include <fstream>
#include "Sales_data.h"

int main(int argc, char **argv){   //命令行参数的处理
    Sales_data total;
    std::ifstream input(argv[1]);
    std::ofstream output(argv[2], std::ofstream::app);   //修改文件模式为app,在文件末尾添加数据

    if(read(input, total)){
        Sales_data trans;
        while(read(input, trans)){
            if(total.isbn() == trans.isbn()) total.combine(trans);
            else{
                print(output, total) << std::endl;
                total = trans;
            }
        }

        print(output, total) << std::endl;
    }else{
        std::cerr << "No Data?!" << std::endl;
    }

    input.close();
    output.close();
    
    return 0;
}