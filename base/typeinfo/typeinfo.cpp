#include <iostream>
#include <typeinfo>

using namespace std;

int main(){
	int c;
	cout << typeid(c).name() << endl;

	//���ֱȽ� �������Զ������ģ��
	if(typeid(c) == typeid(int)){
		cout << "TRUE" << endl;
	}else{
		cout << "FALSE" << endl;
	}
	return 0;
}