#include <iostream>
#include <string>
#include <bitset>

using namespace std;

//bitset是标准带的容器 和 vector<bool> 相似,vector<bool>会进行数据压缩 
int main(){
	//常规初始化方法
	std::bitset<8> b1; // [0,0,0,0,0,0,0,0]
	std::bitset<8> b2(42);	// [0,0,1,0,1,0,1,0]
	std::bitset<8> b3(0xfff0); // [1,1,1,1,0,0,0,0]
	//用字符串初始化bitset
	string str = "110010";
	//后面两个参数为截取str操作，第一个是开始截取位置 第二个为截取长度
	std::bitset<8> b4(str);		// [0,0,1,1,0,0,1,0] 相当于 "110010"
	std::bitset<8> b5(str, 2);	// [0,0,0,0,0,0,1,0] 相当于 "0010"
	std::bitset<8> b6(str, 4);	// [0,0,0,0,0,0,1,0] 相当于 "10"
	std::bitset<8> b7(str, 2, 3); // [0,0,0,0,0,0,0,1] 相当于 "001"
	std::bitset<8> b8(str, 0, 2); // [0,0,0,0,0,0,1,1] 相当于 "11"
	//赋值操作
	b1.set();	//设置b1所有值为true [1,1,1,1,1,1,1,1];
	b2.set(2, true);	//设置b2第3个值为true [0,0,1,0,1,1,1,0]
	b3.reset();	// 设置b3所有值为0 [0,0,0,0,0,0,0,0]
	b2.reset(2);	//b2的第3个值设置为0 [0,0,1,0,1,0,1,0]
	//判断
	bool all = b1.all();	//b1的所有值为true [true]
	bool any = b2.any();	//b2中包含为true的值 [true]
	bool non = b3.none();	//b3中没有值为true [true]
	//to_string操作
	b2.to_string();	// ["00101010"]
	b2.to_string('*');	// ["**1*1*1*"]
	b2.to_string('O', 'X');	// ["OOXOXOXO"]
	//获取该位值
	bool b = b2.test(2);	//test该位为true时返回true 为false返回false
	b = b2[2];	// [false]
	//获取长度
	auto size = b3.size();	// [8]
	//取反
	b6.flip(0);	//第0位取反	[0,0,0,0,0,0,1,1]
	b6.flip(2);	//第2位取反 [0,0,0,0,0,1,1,1]
	b6.flip();	//所有位取反  [1,1,1,1,1,0,0,0]
	//统计
	b8.count();	//[2] 统计bitset里面为true的个数
	//convert
	int i = b2.to_ulong();	//[42]

	return 0;
}