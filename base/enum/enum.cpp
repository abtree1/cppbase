#include<iostream>

using namespace std;

//枚举类型是全局的（非强作用域类型）
//强枚举类型是强作用域类型

//一种结合union的使用方式
struct Student{
	Student(bool g, int a):gender(g),age(a){}
	bool gender;
	int age;
};

class Singer
{
public:
	enum Type {STUDENT, NATIVE, FOREIGNER};

	Singer(bool g, int a):s(g,a){t = STUDENT;}
	Singer(int i):id(i){t = NATIVE;}
	Singer(const char* n, int s){
		int size = (s > 9)?9:s;
		memcpy(name,n,size);
		name[size] = '\0';
		t = FOREIGNER;
	}
	~Singer(){}
private:
	Type t;
	union{
		Student s;
		int id;
		char name[10];
	}
};

Singer(true, 13); //被初始化为STUDENT
Singer(310217);  //被初始化为NATIVE
Singer("J Michael", 9);  //被初始化为FOREIGNER

int main(){
	enum {count = 5};  //enum的行为极像#define的集合
					   //可用于替代#define
	enum class COLOR{Color_Red, Color_Yallow, Color_blue};  //强枚举类型

	int arr[count];
	COLOR c = COLOR::Color_Red;
	if(c == 0){  //不合法 强类型不能隐式转换

	}
	return 0;
}