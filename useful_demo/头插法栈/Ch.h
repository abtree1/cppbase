///
///简单的栈实现，头插法
///
#include<iostream>
using namespace std;
#include<string>
struct ST
{
	int num;
	string str;
	ST *next;
};

class ta
{
public:
	ta(); 
	~ta();
	void create();
	void drop();
	void add();
	void dec();
	void upd();
	void scan();
private:
	ST* header;
};