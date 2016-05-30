#include<iostream>
#include<set>
#include<string>
using namespace std;

int main(){
	set<string> s1;
	set<string> s2 = { "a", "b", "c", "d" };
	cout << s1.empty() << endl;
	s1.swap(s2);
	cout << s1.size() << endl;
	s2.clear();
	//添加元素
	s2.insert({ "a1", "b1", "c1" });
	s2.insert("d1");
	//查询元素
	if (s2.find("c1") != s2.end()){
		cout << "c1 is in s1" << endl;
	}
	//遍历
	for (auto s : s2){
		cout << s <<" ";
	}
	cout << endl;
	//删除
	s1.erase("b");
	auto dit = s1.begin();
	s1.erase(dit);
	for (auto it = s1.begin(); it != s1.end(); ++it){
		cout << (*it) << " ";
	}
	cout << endl;
	return 0;
}