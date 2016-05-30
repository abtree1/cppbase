#include<iostream>
#include<deque>
using namespace std;
int main(){
	deque<int> d1;
	deque<int> d2 = { 1, 2, 3, 4, 5 };
	deque<int> d3 = d2;
	deque<int> d4(10, 2);

	d1.empty();
	//交换
	d4.swap(d3);

	//重新赋值
	d1.assign({ 1, 2, 3, 4, 5, 6, 7 });
	d3.assign(10, 4);
	
	//读取
	cout << d2.back() << endl;
	d2.pop_back();    //只能移除，拿不到被移除的元素
	d2.push_back(8);
	cout << d2.front() << endl;
	d2.pop_front();
	d2.push_front(0);

	cout << d2.at(1) << " ; " << d2[4] << endl;

	//遍历
	for (auto &d : d3){
		d = d * 10;
	}
	return 0;
}