#include "complex.h"

complex &complex::operator=(const complex& lcx){
	this->va = lcx.va;
	this->vb = lcx.vb;
	return *this;
}

complex &complex::operator+=(const complex& lcx){
	this->va += lcx.va;
	this->vb += lcx.vb;
	return *this;
}

int complex::operator[](bool vir){
	if (vir) return this->va;
	return this->vb;
}

complex complex::operator++(){  //前置
	this->va++;
	this->vb++;
	return *this;
}

complex complex::operator++(int){  //后置
	complex c = *this;
	this->va++;
	this->vb++;
	return c;
}

int main(){
	complex com(2,3);
	/*cin >> com;*/
	complex c(1, 1);
	/*cout << (com != c) << endl;*/
	/*com += c;
	cout << com[true] << " " << com[false];*/
	cout << com++ << endl;
	cout << com << endl;
	cout << ++c << endl;
}