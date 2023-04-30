#include <iostream>

using namespace std;

istream& func(istream& in){
    char s;
    while(in.get(s)){
        cout << s;
    }

    if(in.eof()){
        in.clear();
        in.seekg(0);
        cout << "END!" << endl;
    }

    return in;
}

int main(){
    func(cin);
    return 0;
}