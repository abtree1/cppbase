#include"c1.h"

int main()
{
	circle c(1,2,3);
	triangle t(1,2);
	c.area();
	t.area();
	cout<<c.sum()+t.sum()<<endl;
	cout<<endl;
	shape *p[2];
	p[0]=&c;
	p[0]->area();
	p[1]=&t;
	p[1]->area();
	cout<<"sum="<<p[0]->sum()+p[1]->sum()<<endl;
	return 0;
}