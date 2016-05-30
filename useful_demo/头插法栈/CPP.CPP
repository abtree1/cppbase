#include"Ch.h"

ta::~ta() //析构
{
	drop();
}

ta::ta() //构造
{
	header=NULL;
	create();
}

void ta::create() //创建
{
	ST *p;
	
	while(1)
	{
		p=new ST();
		cout << "please input data(num,str): " << endl;
		cin >> p->num >> p->str;
		if(p->num==0)
		{
			delete p;
			break;
		}
		else
		{
			p->next=header;
			header=p;
		}
	}
}

void ta::drop()  //删除
{
	ST *p;
	while(header!=NULL)
	{
		p=header->next;
		delete header;
		header=p;
	}
	cout<<"撤销成功！"<<endl;
}

void ta::add()  //加
{
	int sit,num;
	string str;
	cout << "pleaes input data(sit,num,str):" << endl;
	cin >> sit >> num >> str;
	while(num==0 || sit < 1)
	{
		cout << "unlow data,input again please: " << endl;
		cin >> sit >> num >> str;
	}
	ST *p,*q;
	p=header;
	int count=1;
	while(count<=sit)
	{
		if(!p)
		{
			cout<<"所选位置超过范围"<<endl;
			break;
		}
		if(count==(sit-1) || count == sit) //当插入在栈首时count==sit
		{
			q=new ST();
			q->num=num;
			q->str=str;
			if(sit==1)
			{
				q->next=header;
				header=q;
			}
			else
			{
				q->next=p->next;
				p->next=q;
			}
			cout<<"插入成功"<<endl;
			break;
		}
		p=p->next;
		count++;
	}
	if(count>sit)
	{
		cout<<"插入位置超标"<<endl;
	}
}

void ta::dec()  //减
{
	int sit;
	cout<<"please input sit"<<endl;
	cin>>sit;
	while(sit<=0)
	{
		cout<<"输入信息无效，请重输"<<endl;
		cin>>sit;
	}
	ST *p;
	p=header;
	if(p)
	{
		if(sit==1)
		{
			header=header->next;
			delete p;
			cout<<"删除成功！"<<endl;
		}
		else
		{
			int count=2;
			ST *q;
			while(p)
			{
				q=p;
				p=p->next;
				if(count==sit)
				{
					if(p->next)
					{
						q->next=p->next;
					}
					else 
					{
						q->next=NULL;
					}
					delete p;
					cout<<"删除成功！"<<endl;
					break;
				}
				count++;
			}
			if(count<sit)
			{
				cout<<"输入位置过大!"<<endl;
			}
		}
	}
	else
	{
		cout<<"链表为空！"<<endl;
	}
}

void ta::upd()  //改
{
	int sit,num;
	string str;
	cout<<"input the sit num str.please"<<endl;
	cin>>sit>>num>>str;
	while(sit<=0||num<=0)
	{
		cout<<"输入数据无效，请重新输入"<<endl;
		cin>>sit>>num>>str;
	}
	ST *p;
	p=header;
	int count=1;
	while(p)
	{
		if(count==sit)
		{
			p->num=num;
			p->str=str;
			break;
		}
		p=p->next;
		count++;
	}
	if(count<sit)
	{
		cout<<"位置过大！"<<endl;
	}
}

void ta::scan() //遍历
{
	ST *p;
	p=header;
	int count=1;
	cout<<"**************************************************************"<<endl;
	while(p)
	{
		cout<<"第"<<count<<"条数据:num="<<p->num<<"  str="<<p->str<<endl;
		count++;
		p=p->next;
	}
	cout<<"**************************************************************"<<endl;
}