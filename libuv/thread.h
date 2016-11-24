#pragma once

#include "UVEvent.h"

typedef void (*fun_t)(void* arg);

//����
#if defined (WIN32) || defined(_WIN32)
#define thread_close(t) (CloseHandle(t)!=FALSE)
#define thread_sleep(ms) Sleep(ms)//˯��ms����
#define thread_id GetCurrentThreadId//�õ���ǰ�߳̾��

#elif defined(__linux__)
#define thread_close(t) ()
#define thread_sleep(ms) usleep((ms) * 1000)
#define thread_id pthread_self//�õ���ǰ�߳̾��

#endif

class CThread{
public:
	CThread(string name, fun_t fun);
	~CThread();
public:
	void sleep(unsigned long millsec){thread_sleep(millsec);}
	string& getName(){return mName;} 
	void update();
	bool isRun();
public:
	void createUVLoop();
	void regEvent(CUVEvent* event);
private:
	uv_thread_t mHandle;
	string mName;
	uv_loop_t* mUVloop;
	bool mIsRun;		//false for exit
	vector<CUVEvent*> mEvent_vct;
	uv_mutex_t mMutex;
};