#include "afxh.h"
//#include "obj.h"

#ifndef ISTATE
#define ISTATE

class Obj; //避免重复包含 出现循环包含现象

class IState{
public:
	IState(Obj* obj):mobj(obj){}
	virtual ~IState(){}

	virtual bool enter() = 0;
	virtual bool update() = 0;
	virtual bool exit() = 0;

	virtual Obj* getCurObj() {return mobj;}
private:
	Obj* mobj; //保存对象引用
};

#endif