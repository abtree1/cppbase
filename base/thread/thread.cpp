#include <iostream>
#include <thread>

using namespace std;

void thread_func(string* s, int a) {
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