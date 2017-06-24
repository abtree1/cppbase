#include<iostream>
using namespace std;

class complex
{
public:
	complex(int a = 0, int b = 0) :va(a), vb(b){}
	virtual ~complex(){}
public:
	complex &operator=(const complex &lcx);
	complex &operator+=(const complex &lcx);
	int operator[](bool vir);
	complex operator++();    //前置版本
	complex operator++(int);  //后置版本  
	//一般不要定义类型转换运算符
	//如果要定义，应尽量避免使用隐式类型转换，如下定义
	explicit operator int() const { return va; }
public:
	friend ostream &operator<<(ostream &os, const complex &c);
	friend istream &operator>>(istream &is, complex &c);
	friend complex operator+(const complex &lcx, const complex &rcx);
	friend complex operator-(const complex &lcx, const complex &rcx);
	friend bool operator==(const complex &lcx, const complex &rcx);
	friend bool operator!=(const complex &lcx, const complex &rcx);
private:
	int va;
	int vb;
};

ostream &operator<<(ostream &os, const complex &c){
	os << c.va << "+" << c.vb << "i";
	return os;
}

istream &operator>>(istream &is, complex &c){
	is >> c.va >> c.vb;
	return is;
}

complex operator+(const complex &lcx, const complex &rcx){
	complex oper_tmp;
	oper_tmp.va = lcx.va + rcx.va;
	oper_tmp.vb = lcx.vb + rcx.vb;
	return oper_tmp;
}

complex operator-(const complex &lcx, const complex &rcx){
	complex oper_tmp;
	oper_tmp.va = lcx.va - rcx.va;
	oper_tmp.vb = lcx.vb - rcx.vb;
	return oper_tmp;
}

bool operator==(const complex &lcx, const complex &rcx){
	if (lcx.va == rcx.va && lcx.vb == rcx.vb){
		return true;
	}
	return false;
}

bool operator!=(const complex &lcx, const complex &rcx){
	if (lcx.va != rcx.va || lcx.vb != rcx.vb){
		return true;
	}
	return false;
}