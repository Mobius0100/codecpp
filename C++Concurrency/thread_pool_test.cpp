#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class Task {
public:
    virtual void run() = 0;
};

class ThreadPool {
public:
    ThreadPool(size_t numThreads) : stop(false) {
        for (size_t i = 0; i < numThreads; ++i) {
            threads.emplace_back([this] {
                while (true) {
                    std::unique_ptr<Task> task;
                    
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(lock, [this] { return stop || !tasks.empty(); });
                        
                        if (stop && tasks.empty()) {
                            return;
                        }
                        
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    
                    task->run();
                }
            });
        }
    }
    
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        
        condition.notify_all();
        
        for (std::thread& thread : threads) {
            thread.join();
        }
    }
    
    template<class F, class... Args>
    void enqueue(F&& f, Args&&... args) {
        std::unique_ptr<Task> task = std::make_unique<TaskWrapper<F, Args...>>(std::forward<F>(f), std::forward<Args>(args)...);
        
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.push(std::move(task));
        }
        
        condition.notify_one();
    }
    
private:
    class Task {
    public:
        virtual void run() = 0;
        virtual ~Task() {}
    };
    
    template<class F, class... Args>
    class TaskWrapper : public Task {
    public:
        TaskWrapper(F&& f, Args&&... args) : func(std::move(f)), arguments(std::make_tuple(std::move(args)...)) {}
        
        void run() override {
            std::apply(func, arguments);
        }
        
    private:
        std::function<void(Args...)> func;
        std::tuple<Args...> arguments;
    };
    
    std::vector<std::thread> threads;
    std::queue<std::unique_ptr<Task>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};

class MyTask : public Task {
public:
    void run() override {
        // 执行具体的任务操作
        std::cout << "Running task in thread " << std::this_thread::get_id() << std::endl;
    }
};

int main() {
    ThreadPool pool(4); // 创建一个拥有4个线程的线程池
    
    for (int i = 0; i < 10; ++i) {
        pool.enqueue([] {
            // 在Lambda表达式中执行任务操作
            std::cout << "Running task in thread " << std::this_thread::get_id() << std::endl;
        });
    }
    
    // 等待所有任务完成
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    return 0;
}

