#include "md5.h"

int main(){
	char tmp[128];

	printf("亲，请输入想加密的字符串\n");
	scanf("%s",tmp);
  
	std::string str = md5(tmp);
	printf("%s",str.c_str());

	return 0;
}