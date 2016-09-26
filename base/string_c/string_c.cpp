#include<iostream>
#include<cstring>   //c 语言的string
#include<string>    //c++ 的string
using namespace std;

void input_c();
void output_c();
void io_s_c();
void operator_c();

int main(){
	input_c();
	output_c();
	io_s_c();
	operator_c();

	const char *str1 = "hello ";
	string str2 = "world!";
	cout << "str1 length: " << strlen(str1) << endl;  //计算长度
	if (strcmp(str1, str2.c_str()) > 0){
		cout << "str1 bigger" << endl;
	}else{
		cout << "str2 bigger" << endl;
	}
	cout << "str2 + str1: " << strcat((char *)str2.c_str(), str1) << endl;
	cout << "str2 >> str1: " << strcpy((char *)str2.c_str(), str1) << endl;
	return 0;
}

/*
	为了防止字符串越界，字符串最好先以数组形式定义
*/
void input_c(){
	//几种c的字符串输入方法
	char tmp[256];
	char* ptr;
	scanf("%s", tmp);				//已空格回车等字符结束
	printf("scanf: %s\n", tmp);
	
	ptr = gets(tmp);				//当遇见回车才结束读取，且不存储换行符
	printf("gets: %s\n", tmp);
	printf("gets return: %s\n", ptr);

	ptr = fgets(tmp, 256, stdin);	//当遇见回车或达到最大读取长度结束读取，且存储换行符
	printf("fgets: %s", tmp);
	printf("fgets return: %s", ptr);
}

void output_c(){
	//几种c的字符串输出方法
	puts("puts: hello");  //自动添加换行符
	
	fputs("fputs: hello \n", stdout); //不自动添加换行符

	printf("printf: hello \n");	//可以格式化的输出

	char tmp[64];
	sprintf(tmp, "sprintf hello %d\n", 1);  //格式化输出到数组里面
	puts(tmp);
}

void io_s_c(){
	char tmp[64];
	for (int i = 0; i < 64; ++i)
	{
		if ((tmp[i] = getchar()) == '\n'){
			tmp[i] = '\0';
			break;
		}
	}

	int i = 0;
	while(tmp[i] != '\0')
		putchar(tmp[i++]);
	fputs("\n", stdout);
}

void operator_c(){
	char str1[128];
	char str2[64] = "hello world!";
	char *ps;

	ps = strcpy(str1, str2);
	printf("strcpy: str1: %s, ps: %s \n", str1, ps);

	ps = strncpy(str1 + 6, str2, 5);
	printf("strncpy: str1: %s, ps: %s \n", str1, ps);

	ps = strcat(str1, str2);
	printf("strcat: str1: %s, ps: %s \n", str1, ps);

	ps = strncat(str1, str2, 5);
	printf("strncat: str1: %s, ps: %s \n", str1, ps);

	int i = strcmp(str1, str2);
	printf("str1,str2: %d \n", i);

	i = strncmp(str1, str2, 5);
	printf("str1,str2: %d \n", i);

	ps = strchr(str1, 'o');			//查询字符串中第一个‘o’出现的位置,并在此处截取字符串
	printf("strchr: %s \n", ps);

	ps = strpbrk(str1, "abhol");	//查询后边字符串字符第一次在前面字符串出现的位置,并在此处截取字符串
	printf("strpbrk: strchr: %s \n", ps);

	ps = strrchr(str1, 'o');			//查询字符串中最后一个‘o’出现的位置,并在此处截取字符串
	printf("strrchr: %s \n", ps);

	ps = strstr(str1, str2);		//查询第二个字符串第一次出现在第一个字符串的位置，并在此处截取字符串
	printf("strstr: %s \n", ps);

	size_t t = strlen(str1);
	printf("strlen: %d \n", t);
}