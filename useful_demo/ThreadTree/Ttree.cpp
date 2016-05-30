#include"TTree.h"

Ttree::Ttree(){
	ttree *p = new ttree();
	cout << "请输入一个有效字符:" << endl;
	cin>>p->data;
	if(p->data!='#'){
		head = p;
		create(p);
	}else{
		head = NULL;
		delete p;
	}
}

void Ttree::create(ttree *p){
	ttree *q = new ttree();
	cout<<"请输入一个有效字符(left)"<<endl;
	cin>>q->data;
	if(q->data!='#'){
		p->left=q;
		p->lflag = false;
		create(q);
	}else{
		p->left = NULL;
		p->lflag = true;
		delete q;
	}

	q= new ttree();
	cout<<"请输入一个有效字符(right)"<<endl;
	cin>>q->data;
	if(q->data!='#'){
		p->right=q;
		p->rflag = false;
		create(q);
	}else{
		p->rflag = true;
		p->right = NULL;
		delete q;
	}
}

Ttree::~Ttree(){
	if(head == NULL)
		cout<<"二叉树为空！"<<endl;
	else{
		ttree* p = head;
		ttree* q = p;
		
		while(p!=NULL){
			while(!p->lflag){
				p=p->left;
			}
			q=p;
			p=p->right;
			delete q;
			q=p;
			p=p->right;
			delete q;
		}
	}
//	if(head != NULL)
//		drop(head);
}

void Ttree::drop(ttree *p){
	if(!p->lflag) drop(p->left);
	if(!p->rflag) drop(p->right);
	delete p;
}

void Ttree::preAll(){
	if(head!=NULL){
		pre(head);
	}else{
		cout<<"二叉树为空！"<<endl;
	}
	cout<<endl;
}

void Ttree::pre(ttree *p){
	if(p->left!=NULL) pre(p->left);
	cout<<p->data;
	if(p->right!=NULL) pre(p->right);
}

void Ttree::prethead(){
	if(head!=NULL)
		pthead(head,NULL,NULL);
	else
		cout<<"二叉树为空！"<<endl;
}

void Ttree::pthead(ttree *p,ttree *pl, ttree *pr){
	if(p->left!=NULL){
		pthead(p->left,pl,p);
	}
	else{
		p->left = pl;
		p->lflag = true;
	}
	if(p->right !=NULL){
		pthead(p->right,p,pr);
	}
	else{
		p->right = pr;
		p->rflag = true;
	}
}

void Ttree::tpreAll(){
	if(head == NULL)
		cout<<"二叉树为空！"<<endl;
	else{
		ttree* p = head;
		
		while(p!=NULL){
			while(!p->lflag){
				p=p->left;
			}
			cout<<p->data;
			p=p->right;
			cout<<p->data;
			p=p->right;
		}
	}
}
