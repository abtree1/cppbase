#include <iostream>
#include <string>
#include "json\json.h"

using namespace std;

int main(){
	string jsonstr = "{\"errorno\":0,\"errormsg\":\"\",\"data\":{\"guid\":10117,\"username\":\"z12345\"}}";
	{
		using namespace Json;
		Reader reader;
		Value root;
		reader.parse(jsonstr, root);
		if(root.type() != objectValue){
			cout << "parse error!";
			return 0;
		}
		if(!root["errorno"].isInt()){
			cout << "errorno error" << endl;
			return 0;
		}
		cout << "errorno=" << root["errorno"].asInt() << endl;
		cout << "errormsg=" << root["errormsg"].asString().c_str() << endl;
		if(root["errormsg"].isNull()){
			cout << "msg is null!" << endl;
		}
		if(root["errorno"].isDouble()){
			cout << to_string((int)root["errorno"].asDouble()) << endl;
		}
		if(root["asdasdasd"].asInt() == 0){
			cout << "not key cannot equ 0" << endl;
		}
		if(root["asdasdasd"].isNull()){
			cout << "not key cannot equ 0" << endl;
		}
		root = root["data"];
		cout << "guid=" << root["guid"].asString().c_str() << endl;
		cout << "username=" << root["username"].asString().c_str() << endl;
	}
}