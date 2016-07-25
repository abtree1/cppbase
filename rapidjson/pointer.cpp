#include <iostream>
#include <string>
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\pointer.h"

using namespace std;

void Print(const rapidjson::Document& d){
	using namespace rapidjson;
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);
	cout << buffer.GetString() << endl;
}

int main(){
	{
		using namespace rapidjson;
		Document d;
		Pointer("/project").Set(d, "RapidJson");		//这两个函数行为一致
		SetValueByPointer(d, "/project1", "RapidJson");	//
		Print(d);
		Pointer("/stars").Set(d, 10);			//这两个函数行为一致
		SetValueByPointer(d, "/stars1", 10);	//
		Print(d);
		if(Value* stars = Pointer("/stars").Get(d))			//这两个函数行为一致
			stars->SetInt(stars->GetInt() + 1);
		if(Value* stars1 = GetValueByPointer(d, "/stars1"))	//
			stars1->SetInt(stars1->GetInt() + 1);
		Print(d);
		Pointer("/a/d/0").Create(d);		//这两个函数行为一致
		CreateValueByPointer(d, "/a/d/1");	//
		Print(d);
		Value& hello = Pointer("/hello").GetWithDefault(d, "world");
		Value& hello1 = GetValueByPointerWithDefault(d, "/hello1", "world");
		Print(d);
		Value c("C++");
		Pointer("/hello").Swap(d, c);
		SwapValueByPointer(d, "/hello1", c);
		Print(d);
		
		bool success = false;
		if(GetValueByPointer(d, "/a/d")){		//如果 不确定存在就删除 删除不存在的项会宕机
			success = Pointer("/a/d").Erase(d);
			assert(success);
		}
		if(GetValueByPointer(d, "/a")){
			success = EraseValueByPointer(d, "/a");
			assert(success);
		}
		Print(d);
	}

	return 0;
}