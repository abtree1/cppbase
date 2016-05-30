#include<iostream>
#include<memory>
#include<string>
#include<vector>
using namespace std;

//allocator 分配一块原始内存供程序使用
int main(){
	allocator<string> alloc;  //创建allocator对象
	const size_t g_n = 10;
	auto const g_begin = alloc.allocate(g_n);   //分配g_n大小的未初始化原始内存供使用
	auto g_end = g_begin;
	alloc.construct(g_end++, "hello world!");  //初始化分配的部分内存，并让q指向下一个位置
	vector<string> vi{ "a", "b", "c", "d", "e" };
	g_end = uninitialized_copy(vi.begin(), vi.end(), g_end);  //将vector拷贝到allocator内存中
	g_end = uninitialized_fill_n(g_end, (g_n - vi.size() - 1), "haha");
	for (size_t i = 0; i < g_n; i++){
		cout << *(--g_end) << endl;
		alloc.destroy(g_end);  //销毁初始化分配的内存
	}
	alloc.deallocate(g_begin, g_n);  //释放分配的内存
	return 0;
}