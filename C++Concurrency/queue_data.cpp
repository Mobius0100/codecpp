#include <exception>
#include <memory>
#include <mutex>
#include <stack>
#include <iostream>
#include <thread>
#include <queue>


// 数据类型
struct data_chunk {
  int value;
};

bool more_data_to_prepare() {
  // 判断是否还有更多数据需要准备
  // 在这里简化为固定返回true，表示一直有数据需要准备
  return true;
}

data_chunk prepare_data() {
  // 准备数据
  static int count = 0;
  return {count++};
}

void process(const data_chunk& data) {
  // 处理数据
  std::cout << "Processing data: " << data.value << std::endl;
}

bool is_last_chunk(const data_chunk& data) {
  // 判断是否为最后一块数据
  // 在这里简化为数据值大于等于9时认为是最后一块数据
  return data.value >= 9;
}

std::mutex mut;  // 互斥锁，用于保护对共享数据的访问
std::queue<data_chunk> data_queue;  // 存储数据的队列
std::condition_variable data_cond;  // 条件变量，用于线程间的同步通信

// 数据准备线程函数
void data_preparation_thread()
{
  while (more_data_to_prepare())
  {
    data_chunk const data = prepare_data();  // 准备数据
    std::lock_guard<std::mutex> lk(mut);  // 加锁，保护对共享数据的访问
    data_queue.push(data);  // 将数据放入队列
    data_cond.notify_one();  // 通知数据处理线程有新数据可用
  }
}

// 数据处理线程函数
void data_processing_thread()
{
  while (true)
  {
    std::unique_lock<std::mutex> lk(mut);  // 加锁，保护对共享数据的访问
    data_cond.wait(lk, []{ return !data_queue.empty(); });  // 等待条件满足，即队列中有数据可处理
    data_chunk data = data_queue.front();  // 取出队列中的数据
    data_queue.pop();  // 弹出队列中的数据
    lk.unlock();  // 解锁，允许其他线程访问共享数据
    process(data);  // 处理数据
    if (is_last_chunk(data))
      break;  // 如果是最后一块数据，则退出循环
  }
}


int main() {
  std::thread producer_thread(data_preparation_thread);  // 创建数据准备线程
  std::thread consumer_thread(data_processing_thread);  // 创建数据处理线程

  producer_thread.join();  // 等待数据准备线程结束
  consumer_thread.join();  // 等待数据处理线程结束

  return 0;
}
