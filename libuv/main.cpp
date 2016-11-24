#include "threadMgr.h"
#include "callback.h"

int main(){
	CThreadMgr::create();
	
	CThread* thread = CThreadMgr::getInstance()->createThread("test");

	CUVIdleEvent idle(wait_for_a_write);
	thread->regEvent((CUVEvent*)&idle);

	string s = "this is a test !!!!";
	CUVAsyncEvent async((void*)&s, wait_async);
	thread->regEvent((CUVEvent*)&async);
	Sleep(10);

	thread->regEvent((CUVEvent*)&async);

	CThreadMgr::destory();

	return 0;
}