#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

int main(){
	unordered_map<string, string> um1;
	unordered_map<string, string> um2 = { { "a", "aa" }, { "b", "bb" }, {"c", "cc"} };

	cout << um1.empty() << endl;
	um1.swap(um2);
	cout << um1.size() << endl;
	um2.clear();

	//添加
	um2["c"] = "ccc";
	um2.insert({"a", "aaa"});
	um2.insert(make_pair("v", "vvv"));
	//查询
	cout << um2["a"].c_str() << endl;
	cout << um2.at("c").c_str() << endl;
	auto f = um2.find("v");
	cout << (f->second).c_str() << endl;
	//遍历
	for (auto it = um2.begin(); it != um2.end(); ++it){
		cout << (it->second).c_str() << " ";
	}
	cout << endl;
	//特殊
	//bucket 无序map按bucket存储，每个bucket可以存储多个元素，
	cout << um1.bucket_count() << " "; //容器正在使用的bucket数量
	cout << um1.max_bucket_count() << " "; //容器的最大桶数量
	cout << um1.bucket_size(1) << " ";  //第一个桶中有多少个元素
	cout << um1.bucket("c") << endl; //元素“c”对应的pair在哪个桶 
	
	cout << um1.load_factor() << " ";  //每个bucket的平均元素数量（float）
	cout << um1.max_load_factor() << endl;  //当前维护的桶的最大平均值，

	um1.rehash(um1.max_bucket_count());   //重新设置bucket的个数来重新hash map
	um2.reserve(um1.max_bucket_count()*10);		//重组存储，使得map可以存储n个元素而不用rehash
	//删除
	um1.erase("c");
	um1.erase(um1.begin());
	for (auto i : um1){
		cout << i.second << " ";
	}
	cout << endl;
	return 0;
}