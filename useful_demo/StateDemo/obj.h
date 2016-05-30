//#include "afxh.h"
#include "istate.h"
#include <list>

#ifndef OBJ
#define OBJ

enum Type_State{
	TYPE1 = 0,
	TYPE2,
	TYPEALL
};

struct Event{
	Event(string e):value(e){}

	string value;
};

typedef list<Event> List;

class Obj{
public:
	Obj();
	virtual ~Obj();

	bool changeState(Type_State ts);
	bool update();

	//事件处理相关
	void insert(Event e);
	void operate();
private:
	IState* curstate;
    IState* states[TYPEALL];
	Type_State curtype;

	//事件集合
	List lists;
};

#endif