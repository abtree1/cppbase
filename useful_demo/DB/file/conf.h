#pragma once
#include "../stdafx.h"

class CReadConf:public CSingletion<CReadConf>
{
private:
	CReadConf();
	~CReadConf();

	SINGLETION_FRIEND_CLASS_REGISTER(CReadConf);
public:
	bool readAllData_s(const std::string filename, std::string &out);
	bool writeFile(const std::string filename, void (*fun)(FILE* fp), std::string mode="w");
	bool writeFile(const std::string filename, std::string data, std::string mode="w");
	bool writeBinaryFile(const std::string filename, std::string data, std::string mode="wb");
private:
	FILE* openFile(const std::string filename, std::string mode = "rb,ccs=UTF-8");
	size_t countFileData(FILE* fp);
};