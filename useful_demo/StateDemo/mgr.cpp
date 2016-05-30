#include "mgr.h"

bool Mgr::ProcessCmd(){
	char key;
	if(kbhit()){
		key = getche();
		if(key == 'q'){
			return false;
		}
		if(key == '1'){
			obj->changeState(TYPE1);
		}else if(key == '2'){
			obj->changeState(TYPE2);
		}
		else{			
			string s;   //将char转换为string 
			s = key+'\0';
			Event e(s);
			obj->insert(e);
		}
	}
	return true;
}

Mgr::Mgr(){
}

Mgr::~Mgr(){
	delete obj;
}

bool Mgr::init(){
	obj = new Obj();

	return true;
}

bool Mgr::start(){
	while(true){
		if(!ProcessCmd())
			break;
		obj->update();
		_sleep(10);
	}
	return true;
}