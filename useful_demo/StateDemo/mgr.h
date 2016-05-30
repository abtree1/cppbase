//#include "afxh.h"
#include "obj.h"
#include <conio.h>
#include <stdio.h>

#ifndef MGR
#define MGR

#define STATE_CHANGE_TIME 5

class Mgr{
public:
	Mgr();
	virtual ~Mgr();

	virtual bool init();
	virtual bool start();

	bool ProcessCmd();
private:
	Obj *obj;
	float lasttime;
};

#endif