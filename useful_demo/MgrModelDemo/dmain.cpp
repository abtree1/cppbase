#include "customer.h"
#include "util.h"
#include "goodsMgr.h"

int main(){
	int key = 0;
	Customer customer;
	GoodsMgr goodsMgr;
	string name;
	UINT32 price;
	UINT32 days;
	
	while(true){
		cout<<"请输入指令 0退出 1租赁 2添加物品 3删除物品 4修改物品"<<endl;
		cin >> key;

		if(key == 0)
			break;
		else if(key == 1){
			//添加租赁
			cout<<"请输入名称和天数"<<endl;
			cin>>name>>days;

			Goods *good = goodsMgr.findGoods(name);
			if(good)
				customer.RentGood(good,days);
		}else if(key == 2){
			cout<<"请输入名称"<<endl;
			cin>>name;

			price = (UINT32)RandInt(10,30)*10;
			goodsMgr.addGoods(name,price,(GoodsType)RandInt(0,2));
		}else if(key == 3){
			cout<<"请输入名称"<<endl;
			cin>>name;

			goodsMgr.dropGoods(name);
		}else if(key == 4){
			cout<<"请输入名称"<<endl;
			cin>>name;

			price = (UINT32)RandInt(10,30)*10;
			goodsMgr.updateGoods(name,price,(GoodsType)RandInt(0,2));
		}
	}
	return 0;
}