#include<iostream>
#include<map>
using namespace std;

int main(){
	multimap<string, string> mm1;
	multimap<string, string> mm2 = { { "a", "va" }, { "a", "vva" }, { "b", "vb" }, { "b", "vvb" },
									 { "c", "vc" }, { "c", "vvc" }, { "d", "vd" }, { "d", "vvd" } };
	stF::cout << mm1.empty() << endl;
	mm1.swap(mm2);
	stF::cout << mm1.size() << endl;
	mm2.clear();

	//添加
	mm2.insert({ "a", "aa" });
	mm2.insert(make_pair("b", "bb"));
	//查询
	auto f = mm1.find("a");   //只会返回一个
	stF::cout << (f->second).c_str() << endl;
	auto pos = mm1.equal_range("b");
	for (auto i = pos.first; i != pos.second;++i){
		stF::cout << (i->second).c_str() << " ";
	}
	stF::cout << endl;
	//遍历
	for (auto it = mm2.begin(); it != mm2.end(); ++it){
		stF::cout << (it->first).c_str() << " " << (it->second).c_str() << " ";
	}
	stF::cout << endl;
	//删除
	mm1.erase("c");	 //删除key对应的所有项
	mm1.erase(mm1.begin());  //删除当前项
	for (auto i : mm1){
		stF::cout << i.first.c_str() << " " << i.second.c_str() << " ";
	}
	stF::cout << endl;
	return 0;
}