#include<iostream>
using namespace std;

//static 简单计数器
size_t count_calls(){
	static size_t ctr = 0;
	return ++ctr;
}

int main(){
	for (int i = 0; i < 10; ++i){
		cout << count_calls() << endl;
	}
	return 0;
}