#include "obj.h"

#include "state1.h"
#include "state2.h"

Obj::Obj(){
	states[TYPE1] = new State1(this);
	states[TYPE2] = new State2(this);

	curstate = states[TYPE1];
	curstate->enter();
	curtype = TYPE1;
}

Obj::~Obj(){
	for(int i=0;i<TYPEALL;i++){
	   states[i]->exit();        //此处由于每个数组项对应的实例不同 不能用
	   delete states[i];         //delete [] states;
	}                            //来删除数组
}

bool Obj::changeState(Type_State ts){
	curstate->exit();
	curstate = states[ts];
	curstate->enter();
	curtype = ts;

	return true;
}

bool Obj::update(){
	curstate->update();
	return true;
}

void Obj::insert(Event e){
	lists.push_back(e);
}

void Obj::operate(){
	List::iterator ev = lists.begin();
	while (ev != lists.end())
	{
		cout << ">>>>>>>>>>>>字母"<< ev->value.c_str() << "被点击!" << endl;
        lists.erase(ev);
		ev = lists.begin();
	}
}