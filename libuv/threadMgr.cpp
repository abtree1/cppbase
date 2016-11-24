#include "threadMgr.h"

void entity(void* arg){
	CThread* thread = (CThread*)arg;
	thread->createUVLoop();
	//开始线程循环
	do{
		thread->update();
	}while(thread->isRun());
}

CThreadMgr* CThreadMgr::mInstance = nullptr;

CThreadMgr::CThreadMgr(){
}

CThreadMgr::~CThreadMgr(){
	auto it = mThreadMap.begin();
	while(it != mThreadMap.end()){
		if(it->second){
			delete it->second;
		}
		++it;
	}
}

void CThreadMgr::create(){
	if(nullptr == mInstance)
		mInstance = new CThreadMgr();
}

void CThreadMgr::destory(){
	if(mInstance)
		delete mInstance;
}

CThread* CThreadMgr::createThread(string name){
	CThread* thread = new CThread(name, entity);
	if(thread){
		mThreadMap.insert(make_pair(name, thread));
		return thread;
	}
	return NULL;
}

void CThreadMgr::registerThread(CThread* thread){
	mThreadMap.insert(make_pair(thread->getName(), thread));
}

bool CThreadMgr::stopThread(string name){
	auto it = mThreadMap.find(name);
	if(it == mThreadMap.end()){
		return false;
	}
	//it->second->stop();
	delete it->second;
	mThreadMap.erase(it);
	return true;
}

bool CThreadMgr::stopThread(CThread* thread){
	if(!thread) return false;

	auto it = mThreadMap.find(thread->getName());
	if(it == mThreadMap.end()){
		//thread->stop();
		delete thread;
		return true;
	}

	//thread->stop();
	delete thread;
	mThreadMap.erase(it);
	return true;
}