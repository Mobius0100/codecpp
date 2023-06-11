/*
    
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

class Employee{
public:
    Employee(){
        id = id_next++;
    }
    Employee(const string &s): name(s){
        id = id_next++;
    }
    void print(){
        cout << name << ": " << id << endl;
    }
    Employee(const Employee& ori):name(ori.name){
        id = id_next++;
    }
    Employee& operator=(const Employee& other) {
        if (this != &other) {
            name = other.name;
            id = id_next++;
        }
        return *this;
    }

private:
    string name;
    int id;
    static int id_next;
};

int Employee::id_next = 0;

int main(){
    Employee emp1;
    Employee emp2("Jhon");
    Employee emp3(emp2);
    emp1 = emp3;

    emp1.print();
    emp2.print();
    emp3.print();

    return 0;
}