// https://en.cppreference.com/w/cpp/thread/lock_guard
#include <thread>
#include <mutex>
#include <iostream>
 
int g_i = 0;
std::mutex g_i_mutex;  // ①
 
void safe_increment()
{
  std::lock_guard<std::mutex> lock(g_i_mutex);  // ②
  ++g_i;

  std::cout << std::this_thread::get_id() << ": " << g_i << '\n';
  // ③
}
 
int main()
{
  std::cout << "main: " << g_i << '\n';
 
  std::thread t1(safe_increment); // ④
  std::thread t2(safe_increment);
 
  t1.join();
  t2.join();
 
  std::cout << "main: " << g_i << '\n';
}