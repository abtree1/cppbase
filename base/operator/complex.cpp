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

//文本运算符只能是全局的
complex operator "" _CI(const char* col, size_t n){ //将形如 "123 i32"_CI 的字符串隐式转换为complex类型对象
	const char* p = col;
	const char* end = col + n;
	const char* pva = col, * pvi = nullptr;

	for(; p != end; ++p){
		if(*p == 'i') pvi = p + 1;
		break;
	}

	int iva = 0;
	int ivi = 0;
	if(pva + 1 != pvi)   //如果不传实数部分 为0
		iva = atoi(pva);  //如果不传虚数部分 为0
	if(pvi != nullper)
		ivi = atoi(pvi);

	return complex(iva,ivi);
}

int main(){
	complex com(2,3);
	/*cin >> com;*/
	complex c{"1 i1"_CI};	//重载的文本运算符初始化
	/*cout << (com != c) << endl;*/
	/*com += c;
	cout << com[true] << " " << com[false];*/
	cout << com++ << endl;
	cout << com << endl;
	cout << ++c << endl;
}