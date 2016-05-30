#include<iostream>
#include<forward_list>
using namespace std;
int main(){
	forward_list<int> fl1;
	forward_list<int> fl2(5, 2);
	forward_list<int> fl3 = { 1, 2, 3, 4, 5 };
	forward_list<int> fl4 = fl2;

	fl1.empty();
	fl2.resize(10, 3);  //改变 fl2 大小，增加5个位置，并填入值3

	//forward_list 操作与list几乎相同，详情见list
	//forward_list 特殊操作
	auto it = fl1.before_begin();   //返回第一个元素前的空元素
	fl1.insert_after(it, 1);  //在it位置之后插入元素
	advance(it, 1);
	fl1.insert_after(it, 3, 2); // 在it位置之后插入3个2
	fl1.insert_after(it, { 4, 5, 6, 7 });   //在it之后插入花括号内的元素
	fl1.insert_after(it, fl3.begin(), fl3.end()); //相当于将fl3拷贝给fl1

	it = fl1.begin();
	advance(it, 4);
	fl1.erase_after(it);  //删除it之后的一个元素

	return 0;
}