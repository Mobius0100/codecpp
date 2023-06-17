#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <cmath>
#include <chrono>
#include <ctime>
#include <mutex>

using namespace std;

static const int MAX = 10e8;
static double sum = 0;
static mutex exclusive;

// 计算平方根之和
void worker(int min, int max){
    for(int i=min; i < max; ++i){
        sum += sqrt(i);
    }
}

// 并发版
void concurrent_worker(int min, int max) {
    double tmp = 0;
    for (int i = min; i <= max; i++) {
        tmp += sqrt(i);
    }

    exclusive.lock(); // 在访问共享数据之前加锁
    sum += tmp;
    exclusive.unlock(); // 访问完成之后解锁
}

// 单线程
void serial_task(int min, int max) {
  auto start_time = chrono::steady_clock::now();
  sum = 0;
  worker(0, MAX);
  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
  cout << "Serail task finish, " << ms << " ms consumed, Result: " << sum << endl;
}

// 简陋并发版
void native_concurrent_task(int min, int max){
    auto start_time = chrono::steady_clock::now();

    unsigned concurrent_count = thread::hardware_concurrency();
    cout << "hardware_concurrency: " << concurrent_count << endl;
    vector<thread> threads;
    min = 0;
    sum = 0;
    for(int t=0; t < concurrent_count; ++t){
        int range = MAX / concurrent_count * (t+1);
        threads.push_back(thread(concurrent_worker, min, range));  // 直接使用worker会存在条件竞争
        min = range + 1;
    }

    for(auto &t : threads){
        t.join();
    }

    auto end_time = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    cout << "Concurrent task finish, " << ms << " ms consumed, Result: " << sum << endl;
}

int main(){
    serial_task(0, MAX);
    native_concurrent_task(0, MAX);

    return 0;
}