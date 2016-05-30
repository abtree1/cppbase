#include<iostream>
#include<stdio.h>
#include<malloc.h>
#define MAX 25
using namespace std;

typedef struct
{
	char data;
	int weight;
	int parent;
	int lchild;
	int rchild;
} HTNode;
typedef struct
{   
	char cd[MAX];
	int start;
} HuffmanCode;
int main()
{
	HTNode ht[2*MAX];
	HuffmanCode hcd[MAX], d;
	int i, k, f, l, r, n, c, s1, s2;
    cout<<"* * * * * * * * * * * * * * * * * * * * * \n"
	    <<"\t哈夫曼编码与译码系统\n"
		<<"* * * * * * * * * * * * * * * * * * * * * \n";
	cout<<"\n请输入哈夫曼码元素个数：";
	cin>>n;
	cout<<"请输入各个元素的结点值与权值:\n";
	for(i=1;i<=n;i++)
	{
		cout<<"  第"<<i<<"个元素-->\n\t结点值：";
		cin>>&ht[i].data;
		cout<<"\t权  值：";
		cin>>ht[i].weight;
	}
	for(i=1;i<=2*n-1;i++)
		ht[i].parent=ht[i].lchild=ht[i].rchild=0;

	for(i=n+1;i<=2*n-1;i++)
	{
		s1=s2=32767;
		l=r=0;
		for(k=1;k<=i-1;k++)
			if(ht[k].parent==0)
				if(ht[k].weight<s1)
				{
					s2=s1;
					r=l;
					s1=ht[k].weight;
					l=k;
				}
				else if(ht[k].weight<s2)
				{
					s2=ht[k].weight;
					r=k;
				}
				ht[l].parent=i;
				ht[r].parent=i;
				ht[i].weight=ht[l].weight+ht[r].weight;
				ht[i].lchild=l;
				ht[i].rchild=r;
	}
	for(i=1;i<=n;i++)
	{
		d.start=n+1;
		c=i;
		f=ht[i].parent;
		while(f!=0)
		{
			if(ht[f].lchild==c)
				d.cd[--d.start]='0';
			else 
				d.cd[--d.start]='1';
			c=f;
			f=ht[f].parent;
		}
		hcd[i]=d;
	}
	cout<<"输出哈夫曼编码：\n";
	for(i=1;i<=n;i++)
	{
		cout<<ht[i].data<<": ";
		for(k=hcd[i].start;k<=n;k++)
			cout<<hcd[i].cd[k];
		cout<<"\n";
	}
l: cout<<"\n请选择编码/译码/退出系统: (B/Y/E):  ";
	char hfm;
	cin>>hfm;
	if(hfm=='e')
		return 0;
	else
	{
		switch(hfm)
		{
		case'b':
			{   
				int q	;
		    	char bs;
				cout<<"\n* * *   哈夫曼编码   * * *\n";
				cout<<"请输入字符代码:  "<<endl;
				for(q=0;q!=10;q++)
				{
					bs=getchar();
					for(i=1;i<=n;i++)
					{
						if (bs==ht[i].data)
						for(k=hcd[i].start;k<=n;k++)
							cout<<hcd[i].cd[k];
					}
				}
				cout<<endl;
			} break;
		case'y':
			{  
				char e;
				int t,u;	
				t=2*n-1;
				cout<<"\n* * *   哈夫曼译码   * * *\n";
				cout<<"\n请输入哈夫曼码:  "<<endl;
				for(u=0;u!=10;u++)
					{
						if(ht[t].lchild!=0)
						{
						e=getchar();
							if(e=='0')
								t=ht[t].lchild;
							else 
								t=ht[t].rchild;
						}
						else 
						{
							cout<<ht[t].data;
							t=2*n-1;
						}
					}
					cout<<endl;
			} break;
		}
		goto l;
	}
	return 0;
}  //ZRC
