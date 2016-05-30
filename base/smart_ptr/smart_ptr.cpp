#include<iostream>
#include<memory>
#include<string>
using namespace std;

int main(){
	//shared_ptr 基础
	shared_ptr<string> sptr0;
	shared_ptr<string> sptr1(new string("hello world!"));
	shared_ptr<string> sptr2 = make_shared<string>("hi!");  //推荐用法
	if (!sptr0){   //sptr0还未定义
		cout << "sptr0 is empty" << endl;
	}
	sptr0.swap(sptr1);
	if (sptr1 && sptr1->empty()){   //sptr1已经定义，但为空
		cout << "sptr1 is empty" << endl;
	}
	cout << *sptr2 << endl;
	cout << "unique " << sptr2.unique() << endl;  //是否是唯一引用	
	sptr1 = sptr2;  //sptr1原来的引用计数器减1，sptr2的引用计数器加1
	cout << "use count " << sptr2.use_count() << endl;  //sptr2的当前引用次数，该方法可能效率很低，建议用于测试
	auto p = sptr0.get();  //获取sptr2的普通指针，注意，不能delete p
	cout << *p << endl;
	string *pt = new string("world!");
	sptr2.reset(pt);  //重置sptr2，并让其指向pt
	//weak_ptr 不会累加引用
	weak_ptr<string> wptr(sptr2);
	wptr.use_count();  //与shared_ptr.use_count()一样
	wptr.expired();  //如果wptr.use_count()，返回true；否则返回false
	wptr.lock();   //如果wptr.expired()为true，返回空指针，否则wptr对应的shared_ptr指针
	//unique_ptr 基础
	unique_ptr<string> uptr0;
	unique_ptr<string> uptr1(new string("hello unique"));
	unique_ptr<string> uptr2 = make_unique<string>("unique");
	uptr0.swap(uptr1);
	string *u = new string("aasdasd");
	uptr1.reset(u);
	auto up = uptr2.get();
	uptr0.release();  //释放
	return 0;
}