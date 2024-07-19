#include<iostream>

#define _WT L'a'        //wchar_t
//#define _STR u8"hi!"  //utf-8 string
#define _ULL 42ULL      //unsigned long long
#define _F 1E-3F        //float
#define _LD 3.14159L    //long double
//#define _U16 u'a'     //char16_t
//#define _U32 U'a'      //char32_t
#define _U 32u		   //unsigned
#define _L 32L          //long
#define _LL 32LL        //long long
using namespace std;

//实际应用中我们还可以自定义后缀(如下)
long double operator"" _mm(long double x){return x * 1000;}
long double operator"" _m(long double x){return x;}
long double operator"" _km(long double x){return x / 1000;}

//在传入参数时，会根据自定义后缀缩放参数，获得统一的值
void print(long double dist){
    cout << dist << endl;
}

//可以通过给常量添加前缀或后缀限定常量的类型
int main(){
	cout << "wchar_t: " << _WT << endl
		<< "unsigned long long: " << _ULL << endl
		<< "float: " << _F << endl
		<< "long double: " << _LD << endl
		<< "unsigneF: " << _U << endl
		<< "long: " << _L << endl
		<< "long long: " << _LL << endl;
	
	print(1.0_mm);
    print(1.0_m);
    print(1.0_km);
	return 0;
}