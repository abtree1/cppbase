#include<iostream>
#include<vector>
#include<memory>

using namespace std;

template <typename T, typename F = less<T>>  //模板作为类型
int compare(const T &v1, const T &v2, F f = F()){
	if (f(v1, v2)) return -1;
	else if (f(v2, v1)) return 1;
	else return 0;
}

template <unsigned N, unsigned M>  //模板作为非类型参数
int compare_s(const char(&p1)[N], const char(&p2)[M]){
	return strcmp(p1, p2);
}

template <typename T = int> class Blob{  //如果要使用默认类型，使用<>,如： Blob<> b;
public:
	typedef T value_type;
	typedef typename vector<T>::size_type size_type;
	Blob();
	Blob(initializer_list<T> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const T &t) { data->push_back(t); }
	void push_back(T &&t) { data->push_back(move(t)); }
	void pop_back();
	T &back();
	T &operator[](size_type i);
private:
	shared_ptr<vector<T>> data;
	void check(size_type i, const string &msg) const;
};

template<typename T> 
Blob<T>::Blob() : data(make_shared<vector<T>>()){}

template <typename T>
Blob<T>::Blob(initializer_list<T> il) : data(make_shared<vector<T>>(il)){}

template<typename T>
void Blob<T>::check(size_type i, const string &msg) const {
	if (i >= data->size()){
		throw out_of_range(msg);
	}
}

template<typename T>
void Blob<T>::pop_back(){
	check(0, "pop back on empty Blob");
	data->pop_back();
}

template<typename T>
T &Blob<T>::back(){
	check(0, "pop back on empty Blob");
	return data->back();
}

template <typename T>
T &Blob<T>::operator[](size_type i){
	check(0, "pop back on empty Blob");
	return (*data)[i];
}

//模板中的友元关系（一对一友元关系）
template<typename T> class Pal;
class C{ //C 是一个普通的非模板
	friend class Pal<C>;   //用类C实例化的Pal对象是C的友元
	template<typename T> friend class Pal2;  //Pal2的所有实例都是C的友元，这种情况无需前置声明
};
template <typename T> class C2{ //C2本身是一个模板类
	friend class Pal<T>; //C2的每个实例将相同实例化的Pal申明为友元，Pal的模板声明必须在作用域之内
	template <typename X> friend class Pal2;  //Pal2的所有实例都是C2的每个实例的友元，不需要前置声明
	friend class Pal3; //Pal3是一个非模板类，它是C2所有实例的友元，Pal3不需要前置声明
};

//模板类中的static成员
template <typename T> class foo{
public:
	static size_t count() { return ctr; }
private:
	static size_t ctr;
};
//模板类的每个static函数和成员都有一个自己的分支，
//因此访问模板类的静态成员时，必须带上对应的类型
//如 foo<int>::count() 访问int分支的ctr
//   foo<string>::count()  访问string分支的ctr

int main(){
	cout << compare(1, 2) << endl;
	cout << compare_s("hello", "hi") << endl;
	Blob<int> square = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (size_t i = 0; i != square.size(); ++i){
		square[i] = i*i;
		cout << square[i] << " ";
	}
	cout << endl;
	return 0;
}

//c++ 11
template<class T, class U = double>
void f(T t = 0, U u = 0);
void g(){
	f(1, 'c');  //f<int, char>(1, 'c')
	f(1);		//f<int, double>(1, 0), 使用了默认模板参数double
	// f();		//错误：T类型无法被推导出来
	f<int>();	//f<int, double>(0,0), 使用了默认模板参数double
	f<int, char>();  //f<int, char>(0,0)
}

//c++ 11 对匿名的支持
template<typename T> 
class X{};

template<typename T> 
void TempFun(T t){
	T u{}; //这样可以为T设置默认值
}

struct A{} a;  //A struct name a A 的实例变量
struct {int i;} b;  //b 是匿名类型变量
typedef struct {int i;}B;  //B 是匿名类型变量

void Fun(){
	struct C{} c;

	X<A> x1;
	X<B> x2;
	X<C> x3;
	TempFun(a);
	TempFun(b);
	TempFun(c);
}

//c++ 11 
//c++ 20 可以用auto直接指定值
template<auto N>
void f(){
    cout << N << endl;
}
void print(){
 	f<13>();	//输出 13
}
//c++ 20