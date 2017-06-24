#include <iostream>
#include <vector>
using namespace std;

class MyData{
public:
	MyData() {
	}
	MyData(initializer_list<int> iv) {    //构造函数使用
		for (auto i = iv.begin(); i != iv.end(); ++i){
			d.push_back(*i);
		}
	}
	~MyData() {
	}
public:
	MyData & operator [] (initializer_list<int> l) {    //重载操作
		idx.clear();
		for (auto i = l.begin(); i != l.end(); ++i){
			idx.push_back(*i);
		}
		return *this;
	}

	MyData & operator = (int v) {
		if (idx.empty() != true) {
			for (auto i = idx.begin(); i != idx.end(); ++i){
				d.resize((*i > d.size()) ? *i : d.size());
				d[*i - 1] = v;
			}
		}
		return *this;
	}

	void Print() {
		for (auto i = d.begin(); i != d.end(); ++i){
			cout << *i << " ";
		}
		cout << endl;
	}

private:
	vector<int> idx;
	vector<int> d;
};

int main() {
	MyData d{1,2,3,4,5,6,7};   //用 initializer_list 构造
	d.Print();
	d[{2, 3, 5}] = 7;		//重载后 可批量修改
	d[{1, 4, 5, 8}] = 4;
	d.Print();
}