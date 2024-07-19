#include<iostream>
#include<cstring>   //c 语言的string
#include<string>    //c++ 的string
using namespace std;

void input_c();
void output_c();
void io_s_c();
void operator_c();
void trans_c();

int main(){
	input_c();
	output_c();
	io_s_c();
	operator_c();
	trans_c();

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

	fprintf(stderr, "fprintf: hello \n", ); //可以指定输出对象

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

void operator_c(){   //后面为unicode对应的函数  再后面为TChar.h定义的通用函数(带_UNICODE宏就映射为unicode函数 不带映射为ansi函数)
	char str1[128];
	char str2[64] = "hello world!";
	char *ps;

	ps = strcpy(str1, str2);  // wcscpy  _tcscpy
	printf("strcpy: str1: %s, ps: %s \n", str1, ps);

	ps = strncpy(str1 + 6, str2, 5);	//wcsncpy  _tcsncpy
	printf("strncpy: str1: %s, ps: %s \n", str1, ps);

	ps = strcat(str1, str2);	// wcscat _tcscat
	printf("strcat: str1: %s, ps: %s \n", str1, ps);

	ps = strncat(str1, str2, 5); //wcsncat _tcsncat
	printf("strncat: str1: %s, ps: %s \n", str1, ps);

	int i = strcmp(str1, str2); //wcscmp _tcscmp
	printf("str1,str2: %d \n", i);

	i = strncmp(str1, str2, 5);	//wcsncmp _tcsncmp
	printf("str1,str2: %d \n", i);

	ps = strchr(str1, 'o');  //wcschr _tcschr			//查询字符串中第一个‘o’出现的位置,并在此处截取字符串
	printf("strchr: %s \n", ps);

	ps = strpbrk(str1, "abhol");  //wcspbrk _tcspbrk	//查询后边字符串字符第一次在前面字符串出现的位置,并在此处截取字符串
	printf("strpbrk: strchr: %s \n", ps);

	ps = strrchr(str1, 'o'); //wcsrchr _tcsrchr			//查询字符串中最后一个‘o’出现的位置,并在此处截取字符串
	printf("strrchr: %s \n", ps);

	ps = strstr(str1, str2); //wcsstr _tcsstr		//查询第二个字符串第一次出现在第一个字符串的位置，并在此处截取字符串
	printf("strstr: %s \n", ps);

	size_t t = strlen(str1);  //wcslen _tcslen
	printf("strlen: %d \n", t);
}

void trans_c(){
	char tmp[] = "12.32asdaswq";
	printf("atoi: %d \n", atoi(tmp));
	printf("atol: %d \n", atol(tmp));
	printf("atof: %f \n", atof(tmp));

	//下面为新的转换函数 建议使用
	char *end;
	long l = strtol(tmp, &end, 10);	//10进制
	printf("strtol: %d , stopped at: %s(%d)\n", l, end, *end);

	unsigned long ul = strtoul(tmp, &end, 16); //16进制
	printf("strtoul: %d , stopped at: %s(%d)\n", ul, end, *end);

	double d = strtod(tmp, &end);
	printf("strtoF: %f , stopped at: %s(%d)\n", d, end, *end);

	puts(itoa(10, tmp, 10)); //建议用sprintf代替itoa使用
}