#include<iostream>
using namespace std;

int sum(const int *begin, const int *end){
	int sum = 0;
	while (begin != end){
		sum += *begin;
		++begin;
	}
	return sum;
}

int sum1(const int *arr, int size){
	int sum = 0;
	for (int i = 0; i < size; ++i){
		sum += *arr++;
	}
	return sum;
}

int main(){
	int Arr[] = { 1, 2, 3, 4, 5, 6 };
	int size = sizeof(Arr)/sizeof(Arr[0]);
	cout << "the sum is: " << sum(Arr, &Arr[size]) << endl;
	cout << "the sum is: " << sum1(Arr, size) << endl;
	return 0;
}