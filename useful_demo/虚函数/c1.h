#include<iostream>
using namespace std;

class shape
{
public:
	virtual void area() =0;
	virtual float sum() =0;
};

class circle:public shape
{
public:
	circle(float,float,float);
	void area();
	float sum();
private:
	float x;
	float y;
	float r;
};

class triangle:public shape
{
public:
	triangle(float,float);
	void area();
	float sum();
private:
	float d;
	float h;
};

