#include<iostream>
#include<array>
using namespace std;
int main(){
	//array 不可改变长度
	//array 初始化
	array<int, 10> arr1;
	array<int, 10> arr2 = { 1, 2, 3, 4, 5 };
	array<int, 10> arr3 = arr2;
	cout << "size: " << arr3.size() << " max_size: " << arr3.max_size() << endl;
	
	arr1.swap(arr3);  //交换 arr1 和 arr3
	cout << "arr1[2]: " << arr1[2] << endl;

	//遍历
	for (auto i : arr1){
		cout << i << endl;
	}
	for (auto i = 0; i < arr2.size(); ++i)
	{
		cout << arr2[i] << endl;
	}
	for (auto it = arr2.begin(); it != arr2.end(); ++it)
	{
		cout << *it << endl;
	}
	return 0;
}