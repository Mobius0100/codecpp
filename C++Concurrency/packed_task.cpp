#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <cmath>
#include <chrono>
#include <ctime>
#include <mutex>
#include <future>

using namespace std;

static const int MAX = 10e8;

// 并发版
double concurrent_worker(int min, int max) {
    double sum = 0;
    for (int i = min; i <= max; i++) {
        sum += sqrt(i);
    }

    return sum;
}

// packed_task - future
double concurrent_task(int min, int max){
    vector<future<double>> results;

    unsigned concurrent_count = thread::hardware_concurrency();
    min = 0;
    for(int i=0; i<concurrent_count; ++i){
        packaged_task<double(int,int)> task(concurrent_count);
        results.push_back(task.get_future());

        int range = max / concurrent_count * (i + 1);
        thread t(std::move(task), min, range);
        t.detach();

        min = range + 1;
    }

    cout << "thread create finish" << endl;
    double sum = 0;
    for(auto &r : results){
        sum += r.get();
    }

    return sum;
}

// future - promise
void concurrent_task(int min, int max, promise<double>* result) { // 不返回值，而是通过promise存放结果
    vector<future<double>> results;

    unsigned concurrent_count = thread::hardware_concurrency();
    min = 0;
    for (int i = 0; i < concurrent_count; i++) {
        packaged_task<double(int, int)> task(concurrent_worker);
        results.push_back(task.get_future()); 

        int range = max / concurrent_count * (i + 1);
        thread t(std::move(task), min, range);
        t.detach();

        min = range + 1;
    }

    cout << "threads create finish" << endl;
    double sum = 0;
    for (auto& r : results) {
        sum += r.get();
    }
    result->set_value(sum); // 一旦这里调用了set_value，其相关联的future对象就会就绪
    cout << "concurrent_task finish" << endl;
}
int main(){
    auto start_time = chrono::steady_clock::now();

    promise<double> sum; // 创建一个promoise来存放结果，并以指针的形式传递进concurrent_task中
    concurrent_task(0, MAX, &sum);

    auto end_time = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    cout << "Concurrent task finish, " << ms << " ms consumed." << endl;
    cout << "Result: " << sum.get_future().get() << endl; // ④

    return 0;
}