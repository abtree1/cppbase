#include "state1.h"
#include "obj.h"

bool State1::enter(){
	cout << "state 1 in" << endl;
	return true;
}

bool State1::update(){
	//Obj *obj = getCurObj();
	//obj->operate();
	//cout << "state 1 update" << endl;
	return true;
}

bool State1::exit(){
	cout << "state 1 out" << endl;
	return true;
}