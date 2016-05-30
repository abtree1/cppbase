#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

int main(){
	//定义排序规则方法有多种
	vector<string> vec1 = { "aa", "cc", "bb" };
	//调用标准库, 使用标准库 大于 排序
	//如果对象中没有定义大于运算，需要重载大于运算符
	sort(vec1.begin(), vec1.end(), greater<string>());
	//使用lambda表达式排序
	sort(vec1.begin(), vec1.end(), [](string a, string b){return a < b; });
	return 0;
}