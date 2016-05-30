#include"Ch.h"

int main()
{
	ta t1;
	/*t1.scan();
	t1.add();
	t1.scan();
	t1.upd();
	t1.scan();
	t1.dec();
	t1.scan();*/
	while(1){
	   int ch;
	   cout<<"请选择（1、添加，2、更改，3、删除，4、浏览，其他、退出）"<<endl;
	   cin>>ch;
	   switch(ch)
	   {
	   case 1:t1.add();break;
	   case 2:t1.upd();break;
	   case 3:t1.dec();break;
	   case 4:t1.scan();break;
	   default:break;
	   }
	   if(ch<1 || ch>4)
		   break;
	}
	return 0;
}