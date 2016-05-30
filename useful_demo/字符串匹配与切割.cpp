#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

int main(){	
	string sp="<Q><N NI=\"2000001\" NN=\"(null)\" NM=\"(null)\" /><RQL><SQ SQI=1000023 SQN=温柔的声音 SQP=3 SQT=1 /></RQL><SMQL></SMQL><DSMAL></DSMQL><BTN><BTNL id=\"1\" name=\"tr:asdasdjkasdjkashjk\" /></BTN></Q>";
	int index = sp.find("<BTNL");
	sp = sp.substr(index,sp.length());
	index = sp.find("id=\"");
	sp = sp.substr(index+4,sp.length());
	index = sp.find("\"");
	sp = sp.substr(0,index);
	cout<<sp<<endl;

	return 0;
}