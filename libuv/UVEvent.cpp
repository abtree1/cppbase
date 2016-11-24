#include "UVEvent.h"

//idle
CUVIdleEvent::CUVIdleEvent(uv_idle_cb fun)
	:cbFun(fun){
}

CUVIdleEvent::~CUVIdleEvent(){
}

void CUVIdleEvent::post(uv_loop_t* loop){
	uv_idle_init(loop, &mIdle);
	uv_idle_start(&mIdle, cbFun);
}

//async
CUVAsyncEvent::CUVAsyncEvent(void* data, uv_async_cb fun):
cbFun(fun){
	mAsync.data = data;
}

CUVAsyncEvent::~CUVAsyncEvent(){
}

void CUVAsyncEvent::post(uv_loop_t* loop){
	uv_async_init(loop, &mAsync, cbFun);
	uv_async_send(&mAsync);
}