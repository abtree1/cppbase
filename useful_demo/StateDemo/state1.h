#include "istate.h"

#ifndef STATE1
#define STATE1

class State1:public IState{
public:
	State1(Obj* obj):IState(obj){}
	~State1(){}

	bool enter();
	bool update();
	bool exit();
};

#endif