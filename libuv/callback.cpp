#include "callback.h"

void wait_for_a_write(uv_idle_t* handle){
	//Sleep(10000);
	puts("idler over");
	uv_idle_stop(handle);
}

void wait_async(uv_async_t* handle){
	string s = *((string *)(handle->data));
	puts(s.c_str());
	Sleep(1000);
	uv_close((uv_handle_t*)handle, NULL);
}