#include "stdafx.h"

class CUVEvent{
public:
	virtual void post(uv_loop_t* loop) = 0;
};

class CUVIdleEvent : public CUVEvent{
public:
	CUVIdleEvent(uv_idle_cb fun);
	virtual ~CUVIdleEvent();
	virtual void post(uv_loop_t* loop);
private:
	uv_idle_t mIdle;
	uv_idle_cb cbFun;
};

class CUVAsyncEvent : public CUVEvent{
public:
	CUVAsyncEvent(void* data, uv_async_cb fun);
	virtual ~CUVAsyncEvent();
	virtual void post(uv_loop_t* loop);
private:
	uv_async_t mAsync;
	uv_async_cb cbFun;
};