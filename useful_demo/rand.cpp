#include <iostream>
#include <time.h>
using namespace std;

static unsigned long next = 1;		//随机数种子
const unsigned int SEEK_BASE = 10000;

void seed0(unsigned int seek){
	//extern unsigned long next;
	::next = seek;
}

unsigned int rand0(){
	//extern unsigned long next;
	::next = ::next*1103515245 + 12345;
	return (unsigned int)(::next/65535)%SEEK_BASE;
}

int main(){
	time_t t = time(NULL);
	printf("%d \n", t);
	seed0(t);
	for(int i = 0; i< 10; ++i){
		printf("%d ", rand0());
	}
	puts("");
	//seed0(clock());
	for(int i = 0; i< 10; ++i){
		printf("%d ", rand0());
	}
	puts("");
	return 0;
}