#include<iostream>
#include<unordered_set>
#include<string>
using namespace std;

int main(){
	unordered_multiset<string> us1;
	unordered_multiset<string> us2 = { "aa", "cc", "aa", "bb", "cc" };

	cout << us1.empty() << endl;
	us1.swap(us2);
	cout << us1.size() << endl;
	us2.clear();

	//插入
	us2.insert("a");
	us2.insert("b");
	us2.insert("a");
	//查询
	cout << us2.count("a") << " ";
	auto f = us2.find("a");
	cout << (*f).c_str() << " ";
	auto pos = us2.equal_range("a");
	for (auto it = pos.first; it != pos.second; ++it){
		cout << (*it).c_str() << " ";
	}
	cout << endl;
	//特殊 bucket
	cout << us1.bucket_count() << " "
		<< us1.max_bucket_count() << " "
		<< us1.bucket_size(1) << " "
		<< us1.bucket("aa") << endl;
	cout << us1.load_factor() << " "
		<< us1.max_load_factor() << endl;
	us1.reserve(us1.max_bucket_count() * 5);
	us1.rehash(us1.max_bucket_count());
	//删除
	us1.erase(us1.begin());
	us1.erase("cc");
	//遍历
	for (auto i : us1){
		cout << i.c_str() << " ";
	}
	cout << endl;

	return 0;
}