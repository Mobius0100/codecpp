/*
    读取一个文件，将每一行存入vector
*/
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

void read_to_vector(istream& in){
    vector<string> result;
    std::ofstream output("./data/8-4_out.txt");
    if(!output){
        cout << "Open Error!" << endl;
        return;
    }

    string str;

    while(getline(in, str)){
        result.push_back(str);
        output << str << " * " << endl;
    }

    output.close();
}

int main()
{
    string s = "/Users/lucifer/Code/CPPLab/C++Plus/data/Loneliness and Wind.txt";

    std::ifstream input(s);

    if(input){
        read_to_vector(input);
    }else{
        cout << "Open file error!" << endl;
        input.close();
    }
    
    return 0;
}
