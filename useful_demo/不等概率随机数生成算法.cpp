#include<iostream>
//#include "vld.h"
#include <vector>
#include <ctime>

using namespace std;

//简单不等概率随机数生成算法
vector<float> avgs;

int main(){
	avgs.push_back(395);
	avgs.push_back(5);
	avgs.push_back(600);

	srand(time(0));

	int a0 = 0;
	int a1 = 0;
	int a2 = 0;

	for (int i=0;i<1000;i++)
	{
		int rnum = rand()%1000;
		int index = 0;

		for (int j = 0;j<avgs.size();j++)
		{
			rnum = rnum-avgs[j];
			if(rnum < 0) {
				index = j;

				if(j == 0) a0++;
				else if(j == 1) a1++;
				else a2++;

				break;
			}
		}
		cout << index << "\t";
	}

	cout << endl << a0 << "\t" << a1 << "\t" <<a2<<endl;

	return 0;
}