#include "istate.h"

#ifndef STATE2
#define STATE2

class State2:public IState{
public:
	State2(Obj* obj):IState(obj){}
	~State2(){}

	bool enter();
	bool update();
	bool exit();
};

#endif