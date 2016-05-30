#include<iostream>
#include<stack>
using namespace std;
int main(){
	stack<int> st1;
	st1.push(5);
	cout << st1.top() << endl;
	st1.pop();
	return 0;
}