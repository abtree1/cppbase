#include "tree.h"

ctree::ctree() //构造函数
{
	stree *p;
	p=new stree;
	cout<<"Please input data(int)" << endl;
	cin>>p->data;
	if(p->data==0)
	{
		tl=NULL;
		delete p;
	}
	else
	{
		tl=p;
		create(p);
	}
}

ctree::~ctree() //析构函数
{
	drop(tl);
}

void ctree::create(stree *p)  //构造函数调用的递归函数
{
	stree *q;
	q=new stree;
	cout<<"Please input data left(int):"<<endl;
	cin>>q->data;
	if(q->data!=0)
	{
		p->pt=q;
		//cout<<"连接成功！"<<endl;
		create(p->pt);
	}
	else
	{
		p->pt=NULL;
		delete q;
		//cout<<"删除成功！"<<endl;
	}
	q=new stree;
	cout<<"Please input data right(int)"<<endl;
	cin>>q->data;
	if(q->data!=0)
	{
		p->nt=q;
		//cout<<"连接成功！";
		create(p->nt);
	}
	else
	{
		p->nt=NULL;
		delete q;
		//cout<<"删除成功！"<<endl;
	}

}

void ctree::drop(stree *root) //析构函数调用的递归函数
{
	if(root!=NULL)
	{
		drop(root->pt);
		drop(root->nt);
		delete root;
		//cout<<"删除成功！"<<endl;
	}
}

void ctree::preorder( ) //前序遍历函数
{
	stree *p=tl;
	pre(p);
	cout<<endl;
}

void ctree::inorder( ) //中序遍历函数
{
	stree *p;
	p=tl;
	if(p!=NULL)
	{
		pre(p->pt);  //调用前序函数
		cout<<p->data;
		post(p->nt);  //调用后续函数
	}
	cout<<endl;
}

void ctree::postorder( )  //后续函数
{
	stree *p=tl;
	if(p!=NULL)
	{
		post(p);
	}
	cout<<endl;
}

void ctree::levelorder( )  //层序函数
{
	stree *queen[10]; //定义一个域较大的临时指针数组
	stree *p=tl;
	int first=0,end=1;
	if(p==NULL) return;
	else
	{
		queen[first]=p;
		while(first!=end)
		{
			cout<<queen[first]->data<<" ";
			p=queen[first];
			if(p->pt!=NULL)
				queen[end++]=p->pt;
			if(p->nt!=NULL)
				queen[end++]=p->nt;
			first++;
		}
	}
}

void ctree::pre(stree *root)  //前序遍历函数调用的递归函数
{
	if(root!=NULL)
	{
		cout<<root->data;
		pre(root->pt);
		pre(root->nt);
	}
}

void ctree::post(stree *root)  //后续函数调用的递归函数
{
	if(root->pt!=NULL)
		post(root->pt);
	if(root->nt!=NULL)
		post(root->nt);
	cout<<root->data;
}

void ctree::backorder() //反正交换函数
{
	stree *p=tl;
	if(p!=NULL)
		back(p);
	cout<<"·´×ª³É¹¦£¡"<<endl;
}

void ctree::back(stree *root) //反正交换函数调用的递归函数
{
	stree *q;
	if(root->pt!=NULL)
		back(root->pt);
	if(root->nt!=NULL)
		back(root->nt);
	q=root->pt;
	root->pt=root->nt;
	root->nt=q;
}