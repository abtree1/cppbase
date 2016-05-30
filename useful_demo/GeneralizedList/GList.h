#include<iostream>
#include<string>
using namespace std;

struct GL{
	char data; //为？表示为广义表
	GL *next; //定义兄弟向(广度)
	GL *child; //定义深度
};

struct Stack{
	GL *p;
	Stack *next;
};

class gList{
public:
	gList();
	~gList();
private:
	GL *head;

	void create(string slist,GL* p,Stack *stack);
	void destory(GL* p);
};