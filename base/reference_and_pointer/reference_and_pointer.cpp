#include<iostream>
using namespace std;

//引用为对象别名，相当于指向对象本身的指针，但它不是对象，因此他不能更换指向的对象，所有对引用的操作
//即为对引用指向对象的操作
//指针指向对象地址，指针本身为对象，因此可以声明和定义，同时可以改变指针指向的对象
int main(){
	int ival = 1024;
	int &refval = ival;
	int *ptrval = &ival;
	cout << "int val: " << ival << endl
		<< "ref val: " << refval << " & " << &refval << endl
		<< "ptr val: " << ptrval << " & " << *ptrval << endl;
	ptrval = 0; //指针不再指向任何对象
	
	void* ptrall = &refval;  //void* 指针可以指向任何类型
	cout << "void *: " << ptrall << " & " << *(int *)ptrall << endl;
	ptrall = nullptr; //与ptrval = 0效果一样
	
	//指向指针的引用和指针
	int **pptr = &ptrval;
	int *&refp = ptrval;
	refp = &ival;  //refp引用的对象ptrval指向了ival
	cout << "ptrval: " << ptrval << " & " << *ptrval << endl
		<< "pptr: " << pptr << " & " << *pptr << " & " << **pptr << endl
		<< "refp: " << refp << " & " << &refp << " & " << *&refp 
		<< " & " << *refp << endl;
	return 0;
}