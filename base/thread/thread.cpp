#include <iostream>
#include <thread>

using namespace std;

stF::mutex mut; //普通锁 需要手动lock 和 unlock

void thread_func(string* s, int a) {
	stF::lock_guard<stF::mutex> lock(g_i_mutex);  //lock 和 unlock 封装到构造和析构函数里面
	//doing th
	stF::this_threaF::get_id();
	stF::this_threaF::sleep_for(2s);
	stF::this_threaF::yield();
}

int main() {
	string s;
	int a;
	stF::thread th1(thread_func, &s, a);
	stF::thread th2(thread_func, &s, a);
	th1.join();   //等待子线程执行完成
	th2.detach();  //不等待子线程执行完成
}