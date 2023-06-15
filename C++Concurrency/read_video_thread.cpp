#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <opencv2/opencv.hpp>

const int BUFFER_SIZE = 10;  // 缓冲区大小

std::queue<cv::Mat> buffer;  // 共享的缓冲区
std::mutex mtx;  // 互斥锁
std::condition_variable cond;  // 条件变量

void producer(const std::string& rtspUrl) {
    cv::VideoCapture cap(rtspUrl, cv::CAP_FFMPEG);  // 打开RTSP摄像头
    if (!cap.isOpened()) {
        std::cout << "Failed to open RTSP camera: " << rtspUrl << std::endl;
        return;
    }
    
    while (true) {
        cv::Mat frame;
        cap >> frame;  // 读取视频帧
        
        std::unique_lock<std::mutex> lock(mtx);
        
        // 检查缓冲区是否已满，如果满了则等待
        cond.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });
        
        buffer.push(frame.clone());
        std::cout << "Produced frame from RTSP camera: " << rtspUrl << std::endl;
        
        lock.unlock();
        cond.notify_all();  // 通知消费者可以取出数据了
        
        if (frame.empty()) {
            break;  // 结束生产者线程
        }
    }
}

void consumer() {
    int count = 0;
    
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        
        // 检查缓冲区是否为空，如果为空则等待
        cond.wait(lock, [] { return !buffer.empty(); });
        
        cv::Mat frame = buffer.front();
        buffer.pop();
        
        lock.unlock();
        cond.notify_all();  // 通知生产者可以放入新的数据了
        
        if (frame.empty()) {
            break;  // 结束消费者线程
        }
        
        // 在视频帧上添加矩形
        cv::rectangle(frame, cv::Point(50, 50), cv::Point(200, 200), cv::Scalar(0, 255, 0), 2);
        
        std::string filename = "output" + std::to_string(count) + ".jpg";
        cv::imwrite(filename, frame);  // 保存带矩形的视频帧
        std::cout << "Saved frame: " << filename << std::endl;
        
        count++;
    }
}

int main() {
    std::vector<std::thread> producerThreads;
    std::thread consumerThread(consumer);
    
    // 定义4个RTSP摄像头的URL
    std::vector<std::string> rtspUrls = {
        "rtsp://admin:Admin123456@192.168.1.50:554/Streaming/stream1",
        "rtsp://admin:Admin123456@192.168.1.51:554/Streaming/Channels/101"
    };
    
    // 创建4个生产者线程，分别读取4个RTSP摄像头
    for (const auto& url : rtspUrls) {
        producerThreads.emplace_back(producer, url);
    }
    
    // 等待生产者线程结束
    for (auto& thread : producerThreads) {
        thread.join();
    }
    
    // 添加一个空帧作为结束标志
    std::unique_lock<std::mutex> lock(mtx);
    buffer.push(cv::Mat());
    lock.unlock();
    cond.notify_all();
    
    // 等待消费者线程结束
    consumerThread.join();
    
    return 0;
}
