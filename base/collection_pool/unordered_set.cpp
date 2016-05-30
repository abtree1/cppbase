#include<iostream>
#include<unordered_set>
#include<string>
using namespace std;

int main(){
	unordered_set<string> us1;
	unordered_set<string> us2 = { "a", "c", "b", "s", "e" };
	cout << us1.empty() << endl;
	us1.swap(us2);
	cout << us1.size() << endl;
	us2.clear();
	//插入
	us2.insert("cc");
	us2.insert("aa");
	us2.insert("bb");
	//遍历
	for (auto it = us2.begin(); it != us2.end(); ++it){
		cout << (*it).c_str() << " ";
	}
	cout << endl;
	//特殊 bucket
	cout << us1.bucket_count() << " ";
	cout << us1.max_bucket_count() << " ";
	cout << us1.bucket_size(1) << " ";
	cout << us1.bucket("c") << endl;

	cout << us1.load_factor() << " ";
	cout << us1.max_load_factor() << endl;
	
	us1.rehash(us1.max_bucket_count());
	us1.reserve(us1.max_bucket_count() * 10);
	//删除
	us2.erase("aa");
	us2.erase(us2.begin());
	for (auto i : us2){
		cout << i << " ";
	}
	cout << endl;

	return 0;
}