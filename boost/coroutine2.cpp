#include <iostream>
#include "boost/coroutine2/coroutine.hpp"

using namespace std;

int main() {
	typedef boost::coroutines2::coroutine<int> coro_t2;	//创建一个接受一个int的协程类型
	std::cout << "start coroutine" << std::endl;
	coro_t2::pull_type source(	//定义source为一个读取协程
		[&](coro_t2::push_type& sink) {		//定义sink为一个写入协程
		std::cout << "sink1" << std::endl;
		sink(1);	//写入数据（会暂停source执行）
		std::cout << "sink2" << std::endl;
		sink(2);
		std::cout << "sink3" << std::endl;
		sink(3);
	});
	std::cout << "start while" << std::endl;
	while (source)
	{
		int ret = source.get();		//读取写入的数据
		std::cout << "move to coroutine-function" << ret << std::endl;
		source();	//继续执行source
		std::cout << "back from coroutine-function" << std::endl;
	}
	return 0;
}