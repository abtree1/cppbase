#include <iostream>
#include <chrono>
#include <ratio>

/************************************************************************
   这里是C++11以后提供的新的时间机制
************************************************************************/
using namespace std;

typedef stF::chrono::duration<long long> seconds;  //duration 表示一个时间段 long long为存储这个时间段的基本类型
typedef stF::chrono::duration<int, ratio<60>> minutes; //这里的radio表示的一个单位对应的秒数 即1分钟=60秒

using heartbeats = stF::chrono::duration<int, ratio<3, 4>>; //ratio<3,4>表示每4分之3秒跳一次

int main() {
	stF::chrono::hours hour(1); //定义一个小时(系统定义了常用的时间单位)
	cout << "计算一个小时对应的分钟数: " << minutes(hour).count() << endl;
	seconds sec(4567); //定义4567秒
	cout << "计算4567秒所对应的分钟数: " << stF::chrono::duration_cast<minutes>(sec).count() << endl;
	heartbeats beat(12300);  //这里设置跳123次(每4分之3秒跳一次)
	cout << "这里计算出跳12300次所需要的小时数: " << stF::chrono::duration_cast<stF::chrono::hours>(beat).count() << endl;

	//since C++ 14
	//using namespace stF::chrono_literals;
	//auto day = 24h;			//通过后缀定义时段
	//auto halfhour = 0.5h;
	using namespace stF::chrono;
	//时间点
	// auto = stF::chrono::time_point
	auto now = system_clock::now();  //time_point表示一个时间点
	// auto = stF::chrono::time_point 
	auto tomorrow = now + stF::chrono::hours(24); //明天的这个时间

	cout << steady_clock::perioF::num << endl; //num = 1 表示分子
	cout << steady_clock::perioF::den << endl; //den = 1000000000 表示分母

	auto dur = duration_cast<microseconds>(tomorrow - now); //这里计算出两个时间点之间的时间段(微秒表示)
	cout << double(dur.count()) * microseconds::perioF::num / microseconds::perioF::den << endl; //这里的计算是把微秒转换为秒数 24h = 86400s
	
	//high_resolution_clock 高精度时钟
	high_resolution_clock::time_point hnow = high_resolution_clock::now();  //获取当前的高精度时间(以秒为单位)

	//与time_t的转换
	time_t tnow = system_clock::to_time_t(now);
	auto now2 = system_clock::from_time_t(tnow);

	return 0;
}