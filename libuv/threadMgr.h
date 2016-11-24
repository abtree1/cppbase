#pragma once

#include "thread.h"

class CThreadMgr{
public:
	static void create();
	static void destory();

	static CThreadMgr* getInstance(){return mInstance;}
private:
	static CThreadMgr* mInstance;
public:
	CThread* createThread(string name);
	void registerThread(CThread* thread);
	bool stopThread(string name);
	bool stopThread(CThread* thread);
private:
	CThreadMgr();
	~CThreadMgr();
private:
	map<string, CThread*> mThreadMap;
};