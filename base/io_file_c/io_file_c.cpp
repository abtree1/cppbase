/**
C的文件打开方式
r(b)	只读
w(b)	只写，如果文件不存在会创建文件，如果文件存在，会清空文件现有内容
a(b)	只写，如果文件不存在会创建文件，如果文件存在，追加文件内容
r+(b)	读写
w+(b)	读写，如果文件不存在会创建文件，如果文件存在，会清空文件现有内容
a+(b)	读写，如果文件不存在会创建文件，如果文件存在，写时只能追加文件内容
**/
#include <stdio.h>

void first_way(FILE *fp, const char* p);
void second_way(FILE *fp, const char* p);
void third_way(FILE *fp, const char* p);
void operator_c();
void binary_way(FILE* fp);

int main(){
	const char tmp[] = "this is a test! \njust for test!";
	FILE *fp;
	fp = fopen("t.txt", "w+");
	if(NULL  == fp){
		fprintf(stdout, "read file failed!");
		return 0;
	}
	const char* p = tmp;

	//first_way(fp, p);
	//second_way(fp, p);
	//third_way(fp, p);
	//operator_c();
	binary_way(fp);

	fflush(fp);
	fclose(fp);
	return 0;
}

void first_way(FILE *fp, const char* p){
	while('\0' != *p){
		putc(*p, fp);
		++p;
	}
	rewind(fp);	//返回文件开始处
	char ch;
	while((ch = getc(fp)) != EOF){
		putchar(ch);
	}
}

void second_way(FILE *fp, const char* p){
	fprintf(fp, "fprintf: %s", p);
	rewind(fp);
	char words[16];
	while(fscanf(fp, "%s", words) == 1){
		fputs(words, stdout);
	}
}

void third_way(FILE* fp, const char* p){
	fputs(p, fp);
	rewind(fp);
	char buf[128];
	while(fgets(buf, 128, fp) != NULL && buf[0] != '\0')
		fputs(buf, stdout);
}

/**
fseek	参数
	SEEK_SET	文件开始
	SEEK_CUR	当前位置
	SEEK_END	文件结尾
**/
/**
	fseek函数在某些系统可能不具有兼容性
**/
/**
	对于文件较大，C提供了另外两个定位函数
	fgetpos(FILE* restrict stream, fpos_t* restrict pos);
		将文件当前位置保存下来，成功时返回值为0，pos保存当前位置
	fsetpos(FILE* stream, const fpos_t* pos);
		将文件当前位置设置为pos位置，成功时返回0
**/
void operator_c(){
	FILE *fp;
	fp = fopen("tt.txt", "r");
	if(NULL  == fp){
		fprintf(stdout, "read file failed!");
		return;
	}
	fseek(fp, -1l, SEEK_END);	//将文件指针移动到文件结尾偏移0的位置,不包含文件结束符
	long count = ftell(fp) + 2;	//返回文件当前位置与文件开始位置的字符数（字节数）
	long i = 1;
	while(i != count){
		putchar(getc(fp));
		++i;
		fseek(fp, -i, SEEK_END);
	}
	fclose(fp);
}

void binary_way(FILE* fp){
	double ds[] = {1.0,2.1,3.2,4.3,5.4};
	int is[] = {1,2,3,4};
	fwrite(ds, sizeof(ds), 1, fp);  //第二个参数设置每个数据长度，第三个参数设置数据个数
	fwrite(is, sizeof(int), sizeof(is)/sizeof(int), fp);

	rewind(fp);
	double dr[5];
	int ir[4];
	fread(dr, sizeof(double), 5, fp);
	fread(ir, sizeof(int), 4, fp);
	for(int i = 0;i<5;++i){
		printf("%.1f ", dr[i]);
	}
	puts("");
	for(int i = 0; i< 4;++i){
		printf("%d ", ir[i]);
	}
	puts("");
}