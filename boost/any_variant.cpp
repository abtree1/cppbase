#include <iostream>
#include <string>
#include "boost/variant.hpp"
#include "boost/any.hpp"

class Value {
public:
	template<typename T>
	void SetValue(T val) {
		mVal = val;
	}

	template<typename T>
	T GetValue() {
		return boost::get<T>(mVal);
	}
protected:
	//用于保存值
	boost::variant<int, float, double, std::string, char, bool> mVal;
};

using namespace std;

class CTest {
public:
	int a{};
	int b{};
};

class Any {
public:
	template<typename T>
	void SetValue(T t) {
		any = t;
	}
	template<typename T>
	T GetValue() {
		return boost::any_cast<T>(&any);
	}
public:
	//清空值
	void Clear() {
		any.clear();
	}
	//是否为空值
	bool isEmpty() {
		return any.empty();
	}
	//是否为int值
	bool isInt() {
		return (any.type() == typeid(int));
	}
	//是否为string值(官方文档写法)
	bool isString() {
		return boost::any_cast<std::string>(&any);
	}
private:
	boost::any any;
};

int main() {
	Value v;
	v.SetValue<string>("123");
	cout << v.GetValue<string>().c_str() << endl;
	v.SetValue<int>(32);
	cout << v.GetValue<int>() << endl;
	//下面是any的用法
	boost::any one;
	one = 1;
	cout << boost::any_cast<int>(one) << endl;
	boost::any two;
	two = "abc";
	cout << boost::any_cast<const char *>(two) << endl;
	two = 1;
	cout << boost::any_cast<int>(two) << endl;
	CTest ts;
	ts.a = 1;
	ts.b = 1;
	one = ts;
	ts.a = 2;
	ts.b = 2;
	CTest ts1 = boost::any_cast<CTest>(one);
	cout << ts1.a << " " << ts1.b << endl;
	return 0;
}