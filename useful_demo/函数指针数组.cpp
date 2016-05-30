#include <iostream>
#include <cmath>

using namespace std;

enum EventType{
	TYPE_TEST1,    
	TYPE_TEST2,
	TYPE_COUNT
};

class TestClass{
public:
	void init();
	void test_oper1(int a,int b);
	void test_oper2(int a,int b);
public:
	void callFunc(EventType type,int a,int b);
private:
	void (TestClass::*PTRFUN[TYPE_COUNT])(int,int);
};

void TestClass::init(){
	PTRFUN[TYPE_TEST1] = &TestClass::test_oper1;
	PTRFUN[TYPE_TEST2] = &TestClass::test_oper2;
}

void TestClass::test_oper1(int a,int b){
	cout << "test_oper1   "  << a + b << endl;
}

void TestClass::test_oper2(int a,int b){
	cout << "test_oper2   " << abs(a - b) << endl;
}

void TestClass::callFunc(EventType type,int a,int b){
	(this->*PTRFUN[type])(a,b);
}

int main(){
	TestClass tc;
	tc.init();
	tc.callFunc(TYPE_TEST1,2,2);
	tc.callFunc(TYPE_TEST2,2,1);
}