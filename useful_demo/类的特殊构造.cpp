#include<iostream>
using namespace std;

class Shape
{
private:
	int i;
public:
	Shape(int s)
	{
		i=s;
	}
	void output()
	{
		cout<<i<<endl;
	}
};

int main()
{
	Shape p=static_cast<Shape>(123);
	p.output();
	return 0;
}