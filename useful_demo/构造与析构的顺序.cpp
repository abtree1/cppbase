#include<iostream>
using namespace std;

class CPerson
{
public:
	CPerson()
	{
		cout<<"Person Create!"<<endl;
	}
	virtual ~CPerson()
	{
		cout<<"Person delete!"<<endl;
	}
};

class CMan:public CPerson
{
public:
	CMan()
	{
		cout<<"Man Create!"<<endl;
	}
    ~CMan()
	{
		cout<<"Man delete!"<<endl;
	}
};

int main()
{
	CMan cm;
	return 0;
}