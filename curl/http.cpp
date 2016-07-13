#include <iostream>
#include "curl\curl.h"
#include "curl\easy.h"
using namespace std;

size_t call_wirte_func(const char *ptr, size_t size, size_t nmemb,string* data)  
{
	size_t len  = size * nmemb;  
	if(data!=NULL)
	{
	   	data->append(ptr, len);   
	}
	return len;
}

int get(){
	CURL* pCurl = curl_easy_init();
	if(NULL != pCurl){
		//set head properties
		curl_slist *chunk = curl_slist_append(NULL, "Accept-Encoding: identity;q=1, *;q=0");
		chunk = curl_slist_append(chunk, "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.87 Safari/537.36");
		chunk = curl_slist_append(chunk, "Referer: http://music.163.com/");
		chunk = curl_slist_append(chunk, "Accept-Language: zh-CN,zh;q=0.8");
		chunk = curl_slist_append(chunk, "Accept: */*");
		chunk = curl_slist_append(chunk, "Connection: keep-alive");
		chunk = curl_slist_append(chunk, "Range: bytes=2064384-");

		string url = "http://182.140.231.36/m10.music.126.net/20160627102820/032a24632cc9e0501e0d657ed38f0f98/ymusic/fdb2/d2a7/e7ce/1600f0f2ce4b46bc2e7095e87af67021.mp3?wshc_tag=1&wsts_tag=577089e9&wsid_tag=b68bb8e7&wsiphost=ipdbm";
		curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, chunk);
		curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 120);
		curl_easy_setopt(pCurl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, call_wirte_func);
		string strBuff;
		curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &strBuff);
		
		CURLcode res = curl_easy_perform(pCurl);
		if(CURLE_OK == res){
			cout << strBuff.c_str() << endl;
		}
		curl_slist_free_all(chunk);
		curl_easy_cleanup(pCurl);
	}
	return 0;
}

int post(){
	CURL* pCurl = curl_easy_init();
	if(NULL != pCurl){
		//set head properties
		curl_slist *chunk = curl_slist_append(NULL, "Content-Type:application/json;charset=UTF-8"); 
		chunk = curl_slist_append(chunk, "User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; CIBA)");
		string url = "http://127.0.0.1/index.html";

		curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, chunk);
		curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 120);
		curl_easy_setopt(pCurl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(pCurl, CURLOPT_POST, TRUE);
		string json = "{\"user_name\":\"root\", \"passwd\":\"root\"}";
		curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, json.c_str());
		curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, call_wirte_func);
		string strBuff;
		curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &strBuff);
		curl_easy_setopt(pCurl, CURLOPT_VERBOSE, TRUE);
		
		CURLcode res = curl_easy_perform(pCurl);
		if(CURLE_OK == res){
			cout << strBuff.c_str() << endl;
		}
		curl_slist_free_all(chunk);
		curl_easy_cleanup(pCurl);
	}
	return 0;
}

int main(){
	get();
}