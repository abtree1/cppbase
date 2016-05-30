#include<iostream>
#include<fstream>
#include<string>

using namespace std;

const string TEST_FILE_PATH = "test.ini";

int main(){
	ifstream file;
	file.open(TEST_FILE_PATH, ifstream::in);
	if (!file.is_open()){
		cerr << "打开文件失败！" << endl;
		return 0;
	}
	ofstream outfile;
	string ostr = TEST_FILE_PATH + ".txt";
	outfile.open(ostr, ofstream::out);
	while (!file.eof() && ostr != "<end>"){
		file >> ostr;    //读取，空格结束
		outfile << ostr; //写入
	};
	file.close();
	outfile.flush();
	outfile.close();
	return 0;
}