#include<iostream>
#include<map>
#include<string>
using namespace std;

int main(){
	map<string, int> m1;
	map<string, int> m2 = { { "a", 1 }, { "b", 2 }, { "c", 3 } };
	cout << m1.empty() << endl;
	m1.swap(m2);
	cout << m1.size() << endl;
	m2.clear();
	//map的插入操作
	m2["d"] = 4;   //修改或插入操作
	m2.insert({ "e", 5 });  //隐式make pair
	m2.insert(make_pair("f", 6));   //显示make pair
	pair<string, int> p("g", 7);
	m2.insert(p);
	//map的查找操作
	cout << m2["f"] << endl;   //直接查找
	auto value = m2.at("g");   //相当于直接查找
	cout << value << endl;
	auto search = m2.find("e");
	cout << search->second << endl;
	//map的遍历
	for (auto it = m1.begin(); it != m1.end(); ++it){
		cout << it->second << endl;
	}
	//map删除
	auto dit = m1.begin();
	advance(dit, 2);
	m1.erase(dit);    //删除iterator
	m1.erase("b");    //直接key 删除
	for (auto a : m1){
		cout << a.first << " " << a.second << endl;
	}
	return 0;
}