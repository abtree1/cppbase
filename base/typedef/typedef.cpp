#include<iostream>
 
using namespace std;

typedef double DOUBLE;			//定义 DOUBLE 为 double 的别名
typedef DOUBLE BASE, *pBASE;    //定义 BASE 为 DOUBLE 的别名，pBASE 为 *DOUBLE 的别名

int main(){
	using SI = DOUBLE;   //声明 SI 为 DOUBLE 的别名
	SI si = 1.23;
	cout << "double: " << si << endl;
	const pBASE cstr = 0;  //定义一个*double指针，指向空值 = const double *cstr = 0
	return 0;
}