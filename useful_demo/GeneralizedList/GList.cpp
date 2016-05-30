#include"GList.h"

gList::gList(){
	string slist = "((a),(b,c,(d,e)))";
	Stack *stack;
	if(slist.length()>0){
		char h = slist.at(0);
		string s = slist.substr(1,slist.length());
		if(h == '(')
		{
			head = new GL();
			head->data = '?';
			stack=new Stack();
			stack->p = head;
			head->child = new GL();
			create(s,head->child,stack);
		}else{
			head = new GL();
			head->data=h;
			head->child = NULL;
			head->next=NULL;
		}
	}
}

gList::~gList(){
	if(head==NULL)
		return;
	else if(head->data != '?')
	{
		delete head;
		return;
	}
	else{

	}
}
 
void gList::create(string slist,GL* p,Stack* stack){
	//cout<<slist.at(0)<<endl;
	//cout<<slist.substr(1,slist.length())<<endl;
	if(slist.length()>0)
	{
		char h = slist.at(0);
		string s = slist.substr(1,slist.length());
		if(h == '('){
			p->data='?';
			Stack* st = new Stack();
			st->p = p;
			st->next = stack;
			p->child = new GL();
			create(s,p->child,st);
			//GL* gl=new GL();
			//gl->data='?';
			//p->child=gl;
			//Stack* st = new Stack();
			//st->p = gl;
			//st->next = stack;
			//create(s,gl,st);
		}else if(h == ')'){
			//delete p;
			GL *q = stack->p;
			Stack* st = stack->next;
			delete stack;
			//q->next = new GL();
			create(s,q,st);
		}else if(h == ','){
			p->next = new GL();
			create(s,p->next,stack);
		}else{
			p->data = h;
			p->child = NULL;
			//p->next = new GL();
			create(s,p,stack);
			//GL* gl = new GL();
			//gl->data = h;
			//gl->child=NULL;
			//p->next=gl;
			//create(s,gl,stack );
		}
	}
	int i;

}

void gList::destory(GL *p){
	if(p->child!=NULL)
	{
		destory(p->child);
	}
	if(p->next!=NULL){
		destory(p->next);
	}
	delete p;
}