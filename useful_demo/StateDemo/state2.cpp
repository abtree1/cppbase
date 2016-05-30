#include "state2.h"
#include "obj.h"

bool State2::enter(){
	cout << "state 2 in" << endl;
	return true;
}

bool State2::update(){
	Obj *obj = getCurObj();
	obj->operate();
	//cout << "state 2 update" << endl;
	return true;
}

bool State2::exit(){
	cout << "state 2 out" << endl;
	return true;
}