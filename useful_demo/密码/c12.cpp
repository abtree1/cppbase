#include<iostream>
using namespace std;
#include"c11.h"
void ft::in()
{
	int i;
	cout<<"please input m:";
	for(i=0;i<6;i++)
	{
		cin>>m[i];
		if((m[i]<65)||(m[i]>90&&m[i]<97)||(m[i]>122))
			m[i]='*';
		else if((m[i]>=65&&m[i]<87)||(m[i]>=97&&m[i]<119))
			m[i]+=4;
		else m[i]-=22;
	}
}
void ft::out()
{
	int i;
	for(i=0;i<6;i++)
		cout<<m[i]<<' ';
     cout<<endl;
}