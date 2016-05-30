#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

int main(){
	unordered_multimap<string, string> um1;
	unordered_multimap<string, string> um2 = { { "c", "ccc" },
		{ "b", "bb" }, { "b", "aa" }, { "a", "aa" }, { "c", "cc" } };
	
	cout << um1.empty() << endl;
	um1.swap(um2);
	cout << um1.size() << endl;
	um2.clear();

	//插入
	um2.insert({ "aa", "aaa" });
	um2.insert(make_pair("aa", "aaaa"));
	//查询
	cout << um1.count("b") << " ";
	auto f = um1.find("b");
	cout << (f->second).c_str() << " ";
	auto pos = um1.equal_range("b");
	for (auto it = pos.first; it != pos.second; ++it){
		cout << (it->second).c_str() << " ";
	}
	cout << endl;
	//特殊 bucket
	cout << um1.bucket_count() << " ";
	cout << um1.max_bucket_count() << " ";
	cout << um1.bucket_size(1) << " ";
	cout << um1.bucket("b") << endl;

	cout << um1.load_factor() << " ";
	cout << um1.max_load_factor() << endl;

	um1.rehash(um1.max_bucket_count());
	um1.reserve(um1.max_bucket_count() * 5);
	//删除
	um1.erase(um1.begin());
	um1.erase("b");
	//遍历
	for (auto i : um1){
		cout << i.second.c_str() << " ";
	}
	cout << endl;

	return 0;
}