#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <ctime>
#include <opencv2/opencv.hpp>

const int BUFFER_SIZE = 10;  // 缓冲区大小

std::vector<std::queue<cv::Mat>> buffers;  // 每个摄像头对应的缓冲区
std::mutex mtx;  // 互斥锁
std::condition_variable cond;  // 条件变量

void producer(const std::string& rtspUrl, int cameraIndex) {
    cv::VideoCapture cap(rtspUrl, cv::CAP_FFMPEG);  // 打开RTSP摄像头
    if (!cap.isOpened()) {
        std::cout << "Failed to open RTSP camera: " << rtspUrl << std::endl;
        return;
    }
    
    while (true) {
        cv::Mat frame;
        cap >> frame;  // 读取视频帧
        
        std::unique_lock<std::mutex> lock(mtx);
        
        // 检查对应的缓冲区是否已满，如果满了则等待
        cond.wait(lock, [cameraIndex] { return buffers[cameraIndex].size() < BUFFER_SIZE; });
        
        buffers[cameraIndex].push(frame.clone());
        std::cout << "Produced frame from RTSP camera " << cameraIndex << std::endl;
        
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
        std::vector<cv::Mat> frames;
        std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        {
            std::unique_lock<std::mutex> lock(mtx);
            
            // 检查所有缓冲区是否都有数据，如果有任何一个缓冲区为空，则等待
            cond.wait(lock, [] {
                for (const auto& buffer : buffers) {
                    if (buffer.empty()) {
                        return false;
                    }
                }
                return true;
            });
            
            // 从每个缓冲区中取出一帧
            for (auto& buffer : buffers) {
                cv::Mat frame = buffer.front();
                buffer.pop();
                frames.push_back(frame);
            }
        }
        
        cond.notify_all();  // 通知生产者可以放入新的数据了
        
        if (frames.empty()) {
            break;  // 结束消费者线程
        }
        
        for (int i = 0; i < frames.size(); ++i) {
            cv::Mat frame = frames[i];
            
            // 在视频帧上添加矩形
            cv::rectangle(frame, cv::Point(50, 50), cv::Point(200, 200), cv::Scalar(0, 255, 0), 2);
            
            std::string filename = "camera" + std::to_string(i) + "_frame" + std::to_string(count) + ".jpg";
            cv::imwrite(filename, frame);  // 保存带矩形的帧为图像文件
            
            std::cout << "Consumed frame from RTSP camera " << i << " and saved as " << filename <<  std::ctime(&currentTime) <<  std::endl;
        }
        
        ++count;
    }
}

int main() {
    std::vector<std::string> rtspUrls = {
        "rtsp://admin:Admin123456@192.168.1.51:554/Streaming/Channels/101",
        "rtsp://admin:Admin123456@192.168.1.50:554/Streaming/stream1",
        "rtsp://admin:Admin123456@192.168.1.50:554/Streaming/stream2",
        "rtsp://admin:Admin123456@192.168.1.104:554/cam/realmonitor?channel=1&subtype=0"
    };
    
    buffers.resize(rtspUrls.size());  // 根据摄像头数量初始化缓冲区
    
    std::vector<std::thread> producerThreads;
    
    // 创建生产者线程，分别读取4个RTSP摄像头
    for (int i = 0; i < rtspUrls.size(); ++i) {
        producerThreads.emplace_back(producer, rtspUrls[i], i);
    }
    
    std::thread consumerThread(consumer);  // 创建消费者线程
    
    // 等待生产者线程结束
    for (auto& thread : producerThreads) {
        thread.join();
    }
    
    // 添加一个空帧作为结束标志
    std::unique_lock<std::mutex> lock(mtx);
    for (auto& buffer : buffers) {
        buffer.push(cv::Mat());
    }
    lock.unlock();
    cond.notify_all();
    
    // 等待消费者线程结束
    consumerThread.join();
    
    return 0;
}
