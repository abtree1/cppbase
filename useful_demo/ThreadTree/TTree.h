#include<iostream>
using namespace std;

struct ttree{
	char data;
	ttree *left;
	ttree *right;
	bool lflag;
	bool rflag;
};

/**
本类在前序遍历的基础上实现线索二叉树
*/
class Ttree{
public:
	Ttree();
	~Ttree();

	void preAll();//中序遍历
	void prethead(); //线性化,线索化(中序)
	void tpreAll();//线性化后的中序遍历(会形成死循环)
private:
	ttree *head;
	void create(ttree *p);
	void drop(ttree *p);
	void pre(ttree *p);
	void pthead(ttree *p,ttree *pl,ttree *pr);
};