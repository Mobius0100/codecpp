#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

const int BUFFER_SIZE = 10;  // 缓冲区大小

std::queue<int> buffer;  // 共享的缓冲区
std::mutex mtx;  // 互斥锁
std::condition_variable cv;  // 条件变量

void producer() {
    for (int i = 0; i < 20; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        
        // 检查缓冲区是否已满，如果满了则等待
        cv.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });
        
        buffer.push(i);
        std::cout << "Produced: " << i << std::endl;
        
        lock.unlock();
        cv.notify_all();  // 通知消费者可以取出数据了
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        
        // 检查缓冲区是否为空，如果为空则等待
        cv.wait(lock, [] { return !buffer.empty(); });
        
        int data = buffer.front();
        buffer.pop();
        std::cout << "Consumed: " << data << std::endl;
        
        lock.unlock();
        cv.notify_all();  // 通知生产者可以放入新的数据了
        
        if (data == 19) {
            break;  // 结束消费者线程
        }
    }
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);
    
    producerThread.join();
    consumerThread.join();
    
    return 0;
}
