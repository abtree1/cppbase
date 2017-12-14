#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
//malloc 分配内存块 但不初始化（效率高）
	int *p = (int *)malloc(4*sizeof(int));
	if(p){  //检查空指针是必须的
		for(int i = 0; i < 4; ++i){
			*(p + i) = i;
		}
		for(int i = 0; i < 4; ++i){
			printf("p[%d] is %d \n", i, *(p+i));
		}
		free(p);
	}
//calloc 分配内存块  并清除（初始化）
	int *q = (int *)calloc(4, sizeof(int));
	if(q){
		//realloc 调整之前分配的内存块 realloc 不会初始化 相当于malloc
		//调整大小为8个int  值得注意的是 realloc如果第二个参数传0  相当于free了第一个参数指针所指空间
		int *r = (int*)realloc(q, 8*sizeof(int));
		if(r){
			for(int i = 0; i < 8; ++i){
				printf("r[%d] is %d \n", i, *(r+i));
			}
			free(r);
		}else{
			for(int i = 0; i < 4; ++i){
				printf("q[%d] is %d \n", i, *(q+i));
			}
			free(q);
		}
	}
//指针的数组
	char* pStrs[10]; //定义了含10个指针的数组
	for(int i = 0; i< 10; ++i){
		//注意这里一定要分配4个char的空间 因为字符串结束符占用一个空间 如果分配空间不足 会发生错误
		// pStrs[i] = (char *)malloc(4*sizeof(char));
		// strcpy_s(pStrs[i], 4, "abc");
		//或者用strncpy strncpy 一定会拷贝结算符 所以size要加1
		pStrs[i] = (char *)malloc(3*sizeof(char));
		strncpy_s(pStrs[i], 3, "abc", 2);
	}
	for(int i = 0; i < 10; ++i){
		printf("%d = %s \n",i, pStrs[i]);
	}
//指向数组的指针
	int a[10] = {1};
	int *pa = a;  //一维数组 直接用指针指向首元素
	if(pa){
		for(int i = 0; i < 10; ++i){
			printf("array printer(pa): %d = %d \n", i, *(pa + i));
		}
	}
	//另一种方法(真正指向数组的指针) 必须指定数组长度才能匹配上
	int (*pc)[10];
	pc = &a;
	if(pc){
		for(int i = 0; i < 10; ++i){
			printf("array printer(pc): %d = %d \n", i, (*pc)[i]);
		}
	}
//	int b[10][10] = {{1,1}};
//	int *pb = &b[0][0];  //二维数组
//	if(pb){
//		for(int i = 0; i < 10; ++i){
//			for(int j = 0; j < 10; ++j)
//				printf("array printer(pb): %d = %d \n", i, *(pb + 10 * i + j));
//		}
//	}
	return 0;
}