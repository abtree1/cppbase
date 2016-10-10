#include<iostream>

bool itobs(int n, char* ps){
	const int size = 8*sizeof(int);
	for(int i = size - 1; i >=0; i--,n >>= 1){
		ps[i] = (01 & n) + '0';
	}
	ps[size] = '\0';
	return true;
}

void show_bstr(const char* str){
	int i = 0;
	while(str[i]){
		putchar(str[i]);
		if(++i % 4 == 0 && str[i])
			putchar(' ');
	}
}

int main(){
	char bin_str[8*sizeof(int) + 1];
	int number;
	puts("Enter integers and see them in binary!");
	puts("Non-number input terminates program!");
	while(scanf("%d", &number) == 1){
		itobs(number, bin_str);
		printf("%d is \n", number);
		show_bstr(bin_str);
		putchar('\n');
	}
	return 0;
}