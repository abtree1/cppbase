#include<iostream>
#include<cmath>
using namespace std;
class ftwo
{
public:
	void in();
	void out();
private:
	int a,b,c,d;
};
void ftwo::in()
{
	cout<<"please input abc:";
	cin>>a>>b>>c;
	while(a==0)
	{
		cout<<"input erorr;input again:";
		cin>>a>>b>>c;
	}
}
void ftwo::out()
{
	d=b*b-4*a*c;
	if(d==0)
  cout<<"x1=x2="<<-b/(2*a)<<endl;
	else if(d>0)
		cout<<"x1="<<-b/(2*a)+sqrt(d)/(2*a)<<";"
		    <<"x2="<<-b/(2*a)-sqrt(d)/(2*a)<<endl;
	     else cout<<"x1="<<-b/(2*a)<<"+"<<sqrt(-d)/(2*a)<<"i"<<";"
			 <<"x2="<<-b/(2*a)<<"-"<<sqrt(-d)/(2*a)<<"i"<<endl;
}
ftwo f;
int main()
{
	f.in();
	f.out();
	return 0;
}