#include <iostream>
#include <string>
#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"

using namespace std;

int main(){
	string jsonstr = "{\"errorno\":0,\"errormsg\":\"\",\"data\":{\"guid\":10117,\"username\":\"z12345\"}}";
	{
		using namespace rapidjson;
		Document d;
		d.Parse(jsonstr.c_str());
		Value &s = d["errorno"];
		s.SetInt(s.GetInt() + 1);
		Value &s1 = d["errormsg"];
		s1.SetString("error");

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);

		cout << buffer.GetString() << endl;
	}
}