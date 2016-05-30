#include<iostream>
using namespace std;
int main(){
	cout << "function: " << __FUNCTIONW__ << endl
		<< "line: " << __LINE__ << endl
		<< "file: " << __FILE__ << endl
		<< "date: " << __DATE__ << endl
		<< "time: " << __TIME__ << endl;
	return 0;
}