#include <iostream>
using namespace std;

struct stree
{
	int data;
    stree *pt,*nt;
};

class ctree
{
public:
	ctree();
	~ctree();
	void preorder();  //前序遍历
	void inorder();  //中序遍历
	void postorder(); //后序遍历
	void levelorder();//层序遍历
	void backorder();  //交换所以接点的左右子树
private:
	void drop(stree *root);
	void create(stree *p);
	void pre(stree *root);
	void post(stree *root);
	void back(stree *root);
	stree *tl;
};