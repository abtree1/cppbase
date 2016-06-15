#include<iostream>
#include "hmac.h"
#include<string>
using namespace std;

int main(){
	string key = "012345678";
	string input = "000000";
	unsigned char output[1024];
	UINT32 output_len = 0;
	
	int ret = encrypt::HmacEncode("md5", key.c_str(), key.size(), input.c_str(), input.size(), output, &output_len);
	if(ret == 0){
		cout << "Algorithm HMAC encode succeeded" << endl;
	}else{
		cout << "Algorithm HMAC encode failed" << endl;
		return -1;
	}
	cout << "output length: " << output_len << endl;
	cout << "output: ";
	char buf[129];
	for (int i=0; i<output_len; ++i)
		sprintf(buf+i*2, "%02x", output[i]);
	buf[output_len*2]=0;
	string str(buf);
	cout << str.c_str() << endl;
	return 0;
}