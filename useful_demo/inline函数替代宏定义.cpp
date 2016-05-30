#define CALL_WITH_MAX(a, b) f((a) > (b)?(a):(b))

//下面这个inline函数可以完全替代上面的宏定义，但是下面的函数更安全,建议在需要宏定义的地方，改为下面的函数

template<typename T>
inline void callWithMax(const T& a, const T& b){
	f(a > b ? a : b);
}