#pragma once
#include "stdafx.h"

template<typename T>
class CStore{
public:
	CStore(){}
	~CStore(){}
public:
	bool saveData(string Key, T Data){
		shared_ptr<T> sptr(new T(Data));
		mStores.insert(make_pair(Key, sptr));
		return true;
	}

	T* findData(string Key){
		auto it = mStores.find(Key);
		if(it == mStores.end()){
			return nullptr;
		}
		return it->second.get();
	}
private:
	struct SData{
		shared_ptr<T> sptrData;
		unsigned int endData;
	};
private:
	map<string, SData> mStores;
};

class CStoreMgr
{
public:
	CStoreMgr(){}
	~CStoreMgr(){}
public:
	string constractData(const char* Src, ...){
		va_list param = 0;
		_crt_va_start(param, Src);
		size_t len = _vscprintf(Src, param);
		char *buf = new char[len + 1];
		vsprintf_s(buf, len + 1, Src, param);
		_crt_va_end(param); 
		buf[len] = '\0';
		string ret(buf);
		delete [] buf;
		return ret;
	}

private:

};