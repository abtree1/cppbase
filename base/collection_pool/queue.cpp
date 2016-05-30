#include<iostream>
#include<queue>
using namespace std;

int main(){
	queue<int> q;
	cout << q.empty() << endl;
	q.push(1);
	q.push(2);
	cout << q.front() << " " << q.back() << endl;
	q.pop();
	q.pop();
	return 0;
}