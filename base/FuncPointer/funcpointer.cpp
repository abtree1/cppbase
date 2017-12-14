class CA;

#define CLASS_FUNC(cla, func) &cla::func

/*指向类的非静态成员函数的指针*/
//typedef int (CA::*pClassFun)(int, int);
//c++ 11 加上模板的新写法
template<typename T = CA>
using pClassFun = int (T::*)(int, int);
using ClassFun = pClassFun<CA>;

/*指向一般函数的指针*/
typedef int(*pGeneralFun)(int, int);

class CA{
public:
	int Max(int a, int b){
		return a > b ? a : b;
	}

	int Min(int a, int b){
		return a < b ? a : b;
	}

	static int Sum(int a, int b){
		return a + b;
	}

	/*类内部的接口函数，实现对类的非静态成员函数的封装*/
	int Result(ClassFun fun, int a, int b){
		return (this->*fun)(a, b);
	}

};

/*类外部的接口函数，实现对类的非静态成员函数的封装*/
int Result(CA* pA, ClassFun fun, int a, int b){
	return (pA->*fun)(a, b);
}

/*类外部的接口函数，实现对类的静态成员函数的封装*/
int GeneralResult(pGeneralFun fun, int a, int b){
	return (*fun)(a, b);
}

void f1() {
	printf("function ptr: f1 \n");
}

void f2() {
	printf("function ptr: f2 \n");
}

void main(){
	CA ca;
	int a = 3;
	int b = 4;

	cout << "Test nonstatic member function pointer from member function:" << endl;
	cout << "The maximum number between a and b is " << ca.Result(CLASS_FUNC(CA,Max), a, b) << endl;
	cout << "The minimum number between a and b is " << ca.Result(&CA::Min, a, b) << endl;

	cout << endl;
	cout << "Test nonstatic member function pointer from external function:" << endl;
	cout << "The maximum number between a and b is " << Result(&ca, &CA::Max, a, b) << endl;
	cout << "The minimum number between a and b is " << Result(&ca, &CA::Min, a, b) << endl;

	cout << endl;
	cout << "Test static member function pointer: " << endl;
	cout << "The sum of a and b is " << GeneralResult(CA::Sum, a, b) << endl;

//指向函数的指针数组 声明和调用格式基本一致
	void (*fun_ptr[])(void) = {
		//这里面放函数
		f1,
		f2
	};
	//调用方式如下
	(*fun_ptr[0])();
	(*fun_ptr[1])();
}