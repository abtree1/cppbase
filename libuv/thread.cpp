#include "thread.h"

CThread::CThread(string name, fun_t fun):
mName(name),
mIsRun(true){
	uv_thread_create(&mHandle, fun, this);
	uv_mutex_init(&mMutex);
}

CThread::~CThread(){
	mIsRun = false;
	uv_thread_join(&mHandle);
	uv_loop_close(mUVloop);
	uv_mutex_destroy(&mMutex);
	delete mUVloop;
}

void CThread::createUVLoop(){
	mUVloop = new uv_loop_t();
	uv_loop_init(mUVloop);
}

void CThread::update(){
	if(mEvent_vct.size() <= 0) return;
	for(CUVEvent* event : mEvent_vct){
		event->post(mUVloop);
	}
	mEvent_vct.clear();
	uv_run(mUVloop, UV_RUN_DEFAULT);
}

void CThread::regEvent(CUVEvent* event){
	if(!mIsRun) return;

	uv_mutex_lock(&mMutex);
	mEvent_vct.push_back(event);
	uv_mutex_unlock(&mMutex);
}

bool CThread::isRun(){
	if(mIsRun) return true;
	if(mEvent_vct.size() > 0) return true;
	return false;
}