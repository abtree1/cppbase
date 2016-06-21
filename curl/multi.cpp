#include <string>
#include <iostream>
#include <vector>
#include "curl\curl.h"
#include <time.h>

using namespace std;

size_t curl_writer(void* buffer, size_t size, size_t count, void* stream){
	string* pStream = static_cast<string*>(stream);
	(*pStream).append((char*)buffer, size*count);
	return size*count;
}

/*
*生成一个easy curl对象，进行一些简单设置操作
*/
CURL* curl_easy_handler(const string &sUrl, const string& sProxy, string &sRsp, unsigned int uiTimeout){
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, sUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

	if(!sProxy.empty()){
		curl_easy_setopt(curl, CURLOPT_PROXY, sProxy.c_str());
	}
	//write function
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &sRsp);

	return curl;
}

///**
//* 使用select函数监听mutli curl文件描述符的状态
//* 监听成功返回0，失败返回-1
//*/
//int curl_multi_select(CURLM* curl_m){
//	int ret = 0;
//	timeval timeout_tv;
//	fd_set fd_read;
//	fd_set fd_write;
//	fd_set fd_except;
//	int max_fd = -1;
//	//注意这里一定要清空fd_set， curl_multi_fdset不会执行fdset清空操作
//	FD_ZERO(&fd_read);
//	FD_ZERO(&fd_write);
//	FD_ZERO(&fd_except);
//	//设置select超时时间
//	timeout_tv.tv_sec = 1;
//	timeout_tv.tv_usec = 0;
//	//获取multi curl需要监听的文件描述符集合 fd_set
//	curl_multi_fdset(curl_m, &fd_read, &fd_write, &fd_except, &max_fd);
//	 /** 
//     * When max_fd returns with -1, 
//     * you need to wait a while and then proceed and call curl_multi_perform anyway. 
//     * How long to wait? I would suggest 100 milliseconds at least, 
//     * but you may want to test it out in your own particular conditions to find a suitable value. 
//     */  
//	if(-1 == max_fd){
//		return -1;
//	}
//	 /** 
//     * 执行监听，当文件描述符状态发生改变的时候返回 
//     * 返回0，程序调用curl_multi_perform通知curl执行相应操作 
//     * 返回-1，表示select错误 
//     * 注意：即使select超时也需要返回0，具体可以去官网看文档说明 
//     */  
//	int ret_code = ::select(max_fd + 1, &fd_read, &fd_write, &fd_except, &timeout_tv);
//	switch (ret_code)
//	{
//	case -1:
//		/* select error */ 
//		ret = -1;
//		break;
//	case 0:
//		 /* select timeout */ 
//	default:
//		/* one or more of curl's file descriptors say there's data to read or write*/
//		ret = 0;
//		break;
//	}
//
//	return ret;
//}

const unsigned int MULTI_CURL_NUM = 3;
const string URL = "http://127.0.0.1";
const string PROXY = "";
const unsigned int TIMEOUT = 2000; //ms

/*
*multi curl 使用 demo
*/
int curl_multi_demo(int num){
	//初始化一个multi curl对象
	CURLM* curl_m = curl_multi_init();
	vector<string> RspArray;
	for (int i = 0; i < num; ++i){
		RspArray.push_back("");
	}
	vector<CURL*> CurlArray;
	//设置easy curl对象并添加到multi curl对象中
	for(int idx = 0; idx < num; ++idx){
		CurlArray.push_back(curl_easy_handler(URL, PROXY, RspArray[idx], TIMEOUT)); 
		if(CurlArray[idx] == NULL){
			return -1;
		}
		curl_multi_add_handle(curl_m, CurlArray[idx]);
	}
	 /* 
     * 调用curl_multi_perform函数执行curl请求 
     * url_multi_perform返回CURLM_CALL_MULTI_PERFORM时，表示需要继续调用该函数直到返回值不是CURLM_CALL_MULTI_PERFORM为止 
     * running_handles变量返回正在处理的easy curl数量，running_handles为0表示当前没有正在执行的curl请求 
     */   
	int running_handles;
	while (CURLM_CALL_MULTI_PERFORM == curl_multi_perform(curl_m, &running_handles)){
		cout << running_handles << endl;
	}
	/** 
     * 为了避免循环调用curl_multi_perform产生的cpu持续占用的问题，采用select来监听文件描述符 
     */  
	while (running_handles){
		/*if( -1 == curl_multi_select(curl_m)){
			cerr << "select error" << endl;
			break;
		}else{*/
			// select监听到事件，调用curl_multi_perform通知curl执行相应的操作
			while (CURLM_CALL_MULTI_PERFORM == curl_multi_perform(curl_m, &running_handles)){
				cout << "select: " << running_handles << endl;
			}
		//}
		//cout << "select: " << running_handles << endl;
	}
	// 输出执行结果  
	int msgs_left;
	CURLMsg* msg;
	while ((msg = curl_multi_info_read(curl_m, &msgs_left))){
		if(CURLMSG_DONE == msg->msg){
			int idx;
			for(idx = 0; idx < num; ++idx){
				if(msg->easy_handle == CurlArray[idx])
					break;
			}

			if(idx == num){
				cerr << "curl not found" << endl;
			}else{
				cout << "curl[" << idx << "] completed with status:" << msg->data.result << endl;
				cout << "rsp: " << RspArray[idx] << endl;
			}
		}
	}

	 // 这里要注意cleanup的顺序
	for (int idx = 0; idx < num; ++idx){
		curl_multi_remove_handle(curl_m, CurlArray[idx]);
	}
	for(int idx = 0; idx < num; ++idx){
		curl_easy_cleanup(CurlArray[idx]);
	}
	curl_multi_cleanup(curl_m);
	return 0;
}

/** 
 * 这里要注意cleanup的顺序
 */  
int curl_easy_demo(int num){
	for(int idx = 0; idx < num; ++idx){
		string rsp;
		CURL *curl = curl_easy_handler(URL, PROXY, rsp, TIMEOUT);
		CURLcode code = curl_easy_perform(curl);
		cout << "curl [" << idx << "] completed with status:" << code << endl;
		cout << "rsp: " << rsp << endl;
		//clear handle
		curl_easy_cleanup(curl);
	}
	return 0;
}

#define USE_MULTI_CURL

int main(){
	int num = MULTI_CURL_NUM;
	// 获取开始时间
	clock_t c1 = clock();  // 1/1000Ãë
#ifdef USE_MULTI_CURL   
    // 使用multi接口进行访问
    curl_multi_demo(num);  
#else   
    // 使用easy接口进行访问 
    curl_easy_demo(num);  
#endif   
	 // 获取结束时间
	clock_t c2 = clock();
	cout << "time span: " << c2 - c1 << "(ms)" << endl;
	return 0;
}