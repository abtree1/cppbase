#include"c1.h"

circle::circle(float x1, float y1, float h1):x(x1),y(y1),r(h1){}

void circle::area()
{
	cout<<"circle:"<<endl;
	cout<<"X="<<x<<";"<<"Y="<<y<<endl;
	cout<<"Area="<<this->sum()<<endl;
	cout<<endl;
}

float circle::sum()
{
	float pi=3.1415;
	return pi*r*r;
}

triangle::triangle(float d1, float h1):d(d1),h(h1){}

void triangle::area()
{
	cout<<"triangle:"<<endl;
	cout<<"h="<<h<<";"<<"d="<<d<<endl;
	cout<<"Area="<<this->sum()<<endl;
	cout<<endl;
}

float triangle::sum()
{
	return d*h/2;
}
