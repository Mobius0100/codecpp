/*
    读取一个文件，将其中单词存入vector
*/
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

void read_to_vector(istream& in){
    vector<string> result;
    std::ofstream output("./data/8-5_out.txt");
    
    if(!output.is_open()){
        cout << "Open Error!" << endl;
        return;
    }

    string str;

    while(getline(in, str)){
        std::istringstream iss(str);
        string word;

        while(iss >> word){
            result.push_back(str);
            output << word << "-" << endl;
        } 
        
    }

    output.close();
}

int main()
{
    string s = "./data/Loneliness and Wind.txt";
    std::ifstream input(s);

    if(input){
        read_to_vector(input);
    }else{
        cout << "Open file error!" << endl;
        input.close();
    }
    
    return 0;
}
