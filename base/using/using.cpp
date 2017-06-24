//介绍一些c++ 11 的using 新用法

//using 用作 typedef
template<typename T>
class DefenderT{
public:
	friend T;
	void Defence(int x, int y){
	}
	void Tackle(int x, int Y){
	}
private:
	int pos_x = 15;
	int pos_y = 0;
	int speed = 2;
	int stamina = 120;
};

template<typename T>
class AttackerT{
public:
	friend T;
	void Move(int x, int y){
	}
	void SpeedUp(float radio){
	}
private:
	int pos_x = 0;
	int pos_y = -30;
	int speed = 3;
	int stamina = 100;
};

using Defender = DefenderT<int>;  //普通的类型定义，使用int做参数
using Attacker = AttackerT<int>;

#ifdef UNIT_TEST
class Validator{
public:
	void Validate(int x, int y, DefenderTest& d){}
	void Validate(int x, int y, AttackerTest& a){}
};

using DefenderTest = DefenderT<Validator>;
using AttackerTest = AttackerT<Validator>;

int main(){
	DefenderTest d;
	AttackerTest a;
	a.Move(15,30);
	d.Defence(15,30);
	a.SpeedUp(1.5f);
	d.Defence(15,30);
	Validator v;
	v.Validate(7,0,d);
	v.Validate(1,-10,a);
	return 0;
}
#endif

// using 用于继承父类的函数
class Base{
public:
	Base(){}
	Base(int i){}
	Base(double d, int i){}
	Base(float f, int i, const char* c){}
public:
	void f(double i){
		cout << "Base: " << i << endl;
	}
};

clase Extern : public Base{
public:
	using Base::Base;   //继承base类的所有构造函数
	using Base::f;      //继承base类的f函数

	void f(int i){		//此次定义的f函数参数和基类的f函数不同 所以不会覆盖 相当于子类有两个f函数的重载 
		cout << "Extern: " << i << endl;
	}

};

//委派构造函数
//注意 委派构造函数 不能和 构造函数初始化列表 一起使用
class Info
{
public:
	Info():Info(1){ //形成链状构造函数 (注意 不要形成环状构造函数)
		//基本构造函数执行完成会执行这里面的东西
	}			
	Info(int i):Info(i, 'a'){  //调用基本构造函数

	}
	Info(char e):Info(1, 'e'){

	}
private:
	Info(int i, char e):type(i),name(e){  //作为基本构造函数
		Init();
	}
	void Init(){

	}
	int type{1};
	char name{'a'};
};