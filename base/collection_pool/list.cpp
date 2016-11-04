#include <iostream>
#include <list>
using namespace std;
int main(){
	list<int> li1;
	list<int> li2(10, 1);
	list<int> li3;
	li3.assign(10, 1); //= { 1, 2, 3, 4, 5, 6 };
	list<int> li4 = li3;

	li1.empty();
	li1.assign(5, 2);
	cout << li1.front() << endl;
	li1.pop_front();
	li1.push_front(3);
	cout << li1.back() << endl;
	li1.pop_back();
	li1.push_back(5);

	//list 特有操作
	li1.unique();   //去除重复
	li1.sort();		//merge前 li1必须sort
	li1.merge(li3);  //合并li1 和 li3
	li1.sort();   //排序
	li1.reverse();  //反序
	li1.remove(5);   //排除
	li1.remove_if([](int n){return n < 2; });
	
	//auto it = li2.begin();
	//advance(it, 2);		//向后移动2位
	auto it = li2.end();
	li2.splice(it, li4);   //相当于将li4合并到li2

	li3.splice(li3.begin(), li1, li1.begin(), li1.end());  //相当于交换了li1和li3

	return 0;
}