#include<iostream>
#include<string>
using namespace std;
class MyClass
{
public:
	virtual void OutPut();
};
class SubClass:public MyClass
{
public:
	void OutPut();
};

void MyClass::OutPut()
{
	cout<<"MyClass"<<endl;
}

void SubClass::OutPut()
{
	cout<<"SubClass"<<endl;
}
void out(MyClass &a)
{
	a.OutPut();
}

void main()
{
	SubClass b;
	MyClass *p=&b;
	p->OutPut();
	out(b);
}