#include<iostream>
#include<vector>

using namespace std;

//用vector实现多值返回
vector<int> getThree(){
	return{ 3, 4, 5 };
}

int main(){
	int i = 10;
	// vector 初始化方法
	vector<int> v1;
	vector<int> v2(v1);
	vector<int> v3 = v2;
	vector<int> v4(10, i);//初始化10个值为i的元素
	vector<int> v5(10);//初始化10个空元素，此处值为0
	vector<int> v6{ 1, 2, 3, 4, 5, 6, 7 };//直接赋值
	vector<int> v7 = { 1, 2, 3, 4, 5, 6, 7 };//拷贝赋值

	if (v1.empty()){
		cout << "v1 is empty" << endl;
	}

	cout << "v7.size: " << v7.size() << endl;
	if (v6 < v7){
		cout << "v6 < v7" << endl;
	}
	else if (v6 == v7){
		cout << "v6 == v7" << endl;
	}
	cout << "v4[3]:" << v4[3] << endl;
	//交换两个vector
	v5.swap(v7);
	//清空v7
	v7.clear();
	//遍历方法

	for (auto &i : v5){
		v2.push_back(i); //vector 不能用下标添加元素
	}
	v2.erase(v2[3]); //释放v2[3]
	//vector 也有 insert 操作，但不推荐使用
	auto iti = v2.begin() + 2;
	iti = v2.insert(iti, 3);
	//迭代器（iterator）和（const iterator）
	//在遍历vector时不能向vector中添加元素
	for (auto it = v6.begin(); it != v6.end(); ++it){ //auto == vector<int>::iterator 
		*it = *it * 10;
	}
	for (auto it = v6.cbegin(); it != v6.cend(); ++it){ //auto == vector<int>::const_iterator
		i += *it;
	}
	cout << "i: " << i << endl;
	for (auto it = v6.rbegin(); it != v6.rend(); ++it){ //auto == vector<int>::iterator 
		*it = *it * 10;
	}

	auto vv = getThree();
	cout << vv[0] * vv[1] * vv[2] << endl;

	//顺序容器可像string那样比较大小
	cout << "v6 > v7" << (v6 > v7) << endl;
	return 0;
}