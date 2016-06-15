#include <iostream>
#include "curl\curl.h"
#include "curl\easy.h"
using namespace std;

int ftp_upload(){
	CURL* pCurl = curl_easy_init();
	if(NULL != pCurl){
		string url = "ftp://127.0.0.1:21/iisstart.png";
		string file = "e:/a.png";
		curl_easy_setopt(pCurl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(pCurl, CURLOPT_USERPWD, "root:root");
        curl_easy_setopt(pCurl, CURLOPT_PUT, 1);		//此参数便会创建文件
		FILE* fp = NULL;
        fp = fopen(file.c_str(), "rb");
        if(NULL == fp)
        {
			curl_easy_cleanup(pCurl);
            printf("[Main]fopen (%s) fail!.\n", "a.png");
            return -1;
        }
        fseek(fp, 0l, SEEK_END);
        int nFileSize = (int)ftell(fp);
        if(nFileSize <= 0)
        {
            printf("[CReadFile::ReadFile]ftell error(%d)!\n", nFileSize);
        }
        fseek(fp, 0l, SEEK_SET);
        curl_easy_setopt(pCurl, CURLOPT_INFILE, fp);
        curl_easy_setopt(pCurl, CURLOPT_INFILESIZE, (curl_off_t)(size_t)nFileSize);
        curl_easy_setopt(pCurl, CURLOPT_FTP_CREATE_MISSING_DIRS, 1);
		
		CURLcode res = curl_easy_perform(pCurl);
        if(res != CURLE_OK){
			printf("[CDownIcon::FTPUpload](%s) Upload Fail.\n", url.c_str());
        }
		fclose(fp);
		curl_easy_cleanup(pCurl);
	}
	return 0;
}

//此函数会被多次调用
size_t call_wirte_file(void *buffer, size_t size, size_t nmemb, void *output){
	FILE* fp = static_cast<FILE*>(output);
	fwrite(buffer, size, nmemb, fp);
	return size*nmemb;
}

int ftp_download(){
	CURL* pCurl = curl_easy_init();
	if(NULL != pCurl){
		string url = "ftp://127.0.0.1:21/iisstart.png";
		string file = "e:/b.png";
		curl_easy_setopt(pCurl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(pCurl, CURLOPT_USERPWD, "root:root");
		FILE* fp = NULL;
        fp = fopen(file.c_str(), "wb");		//带写入“w”属性，便会创建文件
        if(NULL == fp)
        {
			curl_easy_cleanup(pCurl);
            printf("[Main]fopen (%s) fail!.\n", "a.png");
            return -1;
        }
		fseek(fp, 0l, SEEK_SET);
		curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, call_wirte_file);
		curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, fp);
		//curl_easy_setopt(pCurl, CURLOPT_VERBOSE, TRUE);  //打印信息用
		
		CURLcode res = curl_easy_perform(pCurl);
        if(res != CURLE_OK){
			printf("[CDownIcon::FTPUpload](%s) Upload Fail.\n", url.c_str());
        }
		fflush(fp);
		fclose(fp);
		curl_easy_cleanup(pCurl);
	}
	return 0;
}