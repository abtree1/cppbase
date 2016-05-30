#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#define TEST_FILE_PATH "test.ini"

/**
对.ini等格式文件的读取方法。
**/
bool ReadTo(std::istream* pStream,char* pch){
	string str;
	*pStream >> str;

	while(str != pch){
		if(pStream->eof() || str == "<end>")
			return false;

		*pStream >> str;
	}

	return true;
}

int main(){
	ifstream file;
	file.open(TEST_FILE_PATH);
	if(!file.is_open())
		return 0;

	string s[5];
	while(ReadTo(&file,"#")){
		file >> s[0];
        file >> s[1];
		file >> s[2];
		file >> s[3];
		file >> s[4];

		cout<<s[0]<<'\t'<<s[1]<<'\t'<<s[2]<<'\t'<<s[3]<<'\t'<<s[4]<<'\n';
	}

	file.close();
	return 1;
}