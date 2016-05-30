#include<iostream>
#include<set>
using namespace std;
int main(){
	multiset<string> ms1;
	multiset<string> ms2{ "a", "a", "b", "b", "c" };

	cout << ms1.empty() << endl;
	ms1.swap(ms2);
	cout << ms1.size() << endl;
	ms2.clear();

	//添加
	ms2.insert({ "aa", "aa", "vv" });
	ms2.insert("bb");
	//查询
	auto a = ms2.find("vv");
	cout << (*a).c_str();
	auto pos = ms2.equal_range("aa");
	for (auto i = pos.first; i != pos.second; ++i){
		cout << (*i).c_str() << " ";
	}
	cout << endl;
	cout << ms1.count("b") << endl;
	//遍历
	for (auto it = ms2.begin(); it != ms2.end(); ++it){
		cout << (*it).c_str() << " ";
	}
	cout << endl;
	//删除
	ms1.erase("b");
	auto dit = ms1.rbegin();  //iterator遵循 [ , ) 左闭右开机制
	++dit;
	ms1.erase(dit.base());
	for (auto i : ms1){
		cout << i.c_str() << " ";
	}
	cout << endl;
	return 0;
}