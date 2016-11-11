#include <iostream>
#include <typeinfo>

using namespace std;

int main(){
	int c;
	cout << typeid(c).name() << endl;

	//这种比较 可用于自定义类和模板
	if(typeid(c) == typeid(int)){
		cout << "TRUE" << endl;
	}else{
		cout << "FALSE" << endl;
	}
	return 0;
}