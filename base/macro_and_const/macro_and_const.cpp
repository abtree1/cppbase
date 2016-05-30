#include <iostream>
#define PI 3.14f
using namespace std;
extern int e = 5;

class const_test{
private:
	static const int mVal = 10;		//定义常量对象 取代#define
									//新版的c++编译器允许直接在定义时赋值
									//声明为static是为了保证只有一个拷贝，而不是一个实例一个
	static const int* const mpVal;  //常量指针声明需要两个const，前一个现在赋值为常量，后一个限制指针为常量
};

// const int const_test::mVal = 10;  //老式的静态常量赋初值操作
const int* const const_test::mpVal = &const_test::mVal;

int main(){
	const int r = 10;
	cout << "Pi: " << PI << " R: " << r << " Pi*R*R: " << PI*r*r << endl;

	//如果想在多个文件中使用同一个const常量
	//可将const常量定义和声明为extern
	//或将const定义在公共头文件里面
	extern int e;
	cout << "e: " << e << endl;

	//const 常量引用
	int i = 4;
	const int &refr = i;  //i的值可变，但不允许通过refr改变i的值
	cout << "refr: " << refr << endl;

	//const 指针
	const int *ptri = &i;
	//int *ptrr = &r; 不合法
	const int *ptrr = &r;
	cout << "ptri: " << *ptri << endl
		<< "ptrr: " << *ptrr << endl;

	//top-level const 表示指针本身是一个const
	//low-level const 表示指针所指对象是一个const
	int *const p1 = &i;			//不能改变p1的值，因为声明p1是一个常量指针(top-level)
	const int ci = 43;			//不能改变ci的值，因为ci是一个常量(top-level)
	const int *p2 = &ci;		//可以改变p2的值，因为声明p2指向一个常量，并非p2是常量指针(low-level)
	const int *const p3 = p2;	//即声明p3是个常量指针，又声明p3指向常量(low-level, top-level)
	const int &rrr = ci;			//引用本身为常量，const声明引用对象为常量(low-level)
	i = ci;			//合法，i为常量
	p2 = p3;		//合法，p2和p3拥有相同的low_level const，且p2本身为常量指针
	//int *p = p3;  //非法，p和p3的low_level const 不同
	p2 = &i;		//合法， 允许int* 转换为 const int*
	//int &rr = ci;  //非法， 不能变量引用常量
	const int &rr = i; //合法，允许常量引用变量

	//constexpr 目前并不支持
	//constexpr int mf = 20;				//合法，constexpr 必须在编译时就确定 const常量的值
	//constexpr int sz = get_size();    //非法，编译时不能确定const常量值
	//constexpr int sz = gsize();       //非法，依然不能再编译时确定sz的值
	//constexpr int sz = size();			//合法，在编译时确定sz的值
	//constexpr int *ptr = 0;         //合法，声明指针ptr为constexpr	
	return 0;
}

//int get_size(){
//	return 12;
//}
//
//const int gsize(){
//	return 12;
//}
//
//constexpr int size(){
//	return 12;
//}