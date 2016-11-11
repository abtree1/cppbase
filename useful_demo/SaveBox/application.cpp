#include "stdafx.h"
#include <typeinfo>

struct sc{
	int i;
	string s;
	float f;
};

int main(){
	/*CStore<int> store;
	store.saveData("1", 1);
	int* i = store.findData("1");
	cout << *i << endl;

	CStore<string> store_s;
	store_s.saveData("1", "a");
	string* str = store_s.findData("1");
	cout << (*str).c_str() << endl;
	
	if((typeid(store_s) == typeid(CStore<int>))){
		cout << "TRUE" << endl;
	}else{
		cout << "FALSE" << endl;
	}*/
	
	/*FILE *fp = fopen("b.dat", "wb");
	if(fp == NULL)
		return 0;

	7890-*-sc cs;
	cs.i = 1;
	cs.s = "abc";
	cs.f = 1.0;
	size_t size = sizeof(cs);

	fwrite(&cs, size, 1, fp);
	fflush(fp);
	fclose(fp);

	fp = fopen("b.dat", "rb");
	sc ds;
	fread(&ds, size, 1, fp);*/

	/*size_t size = sizeof(cs);
	char* buf = new char[size];
	memcpy(buf, &cs, size);*/

	//sc ds;
	//memmove(&ds, buf, size);
	//memcpy(&ds, buf, size);
	//cout << ds.i << " +++ " << ds.s << " +++ " << ds.f << endl;
	//delete [] buf;
	//fclose(fp);
	CStoreMgr sm;
	string s = sm.constractData("%s_%d_%0.1f", "aaa", 1, 1.1);
	int i;
	string ss;
	float f;
	sscanf(s.c_str(), "%3s_%d_%0.1f", &ss, &i, &f);
	cout << i <<endl
		<< s <<endl
		<< f << endl;
	
	return 0;
}