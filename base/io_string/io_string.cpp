#include<iostream>
#include<sstream>
using namespace std;
int main(){
	string str = "aaaa bbbb cccc dddd ";
	istringstream istr(str);
	ostringstream ostr;
	string tstr;
	while (istr >> tstr){
		cout << tstr << endl;
		ostr << tstr << " ";
	}
	cout << ostr.str() << endl;
	return 0;
}