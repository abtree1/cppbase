#include<iostream>
int main(){
	const int n=2;
	int **p=new int*[n];
	for(int i=0;i<n;i++)
	p[i]=new int[n];
	p[0][0]=1;
	std::cout<<p[0][0]<<std::endl;
	delete [] p;
}