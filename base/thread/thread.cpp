#include <iostream>
#include <thread>

using namespace std;

std::mutex mut; //普通锁 需要手动lock 和 unlock

void thread_func(string* s, int a) {
	std::lock_guard<std::mutex> lock(g_i_mutex);  //lock 和 unlock 封装到构造和析构函数里面
	//doing th
	std::this_thread::get_id();
	std::this_thread::sleep_for(2s);
	std::this_thread::yield();
}

int main() {
	string s;
	int a;
	std::thread th1(thread_func, &s, a);
	std::thread th2(thread_func, &s, a);
	th1.join();   //等待子线程执行完成
	th2.detach();  //不等待子线程执行完成
}