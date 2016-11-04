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
	bool writeStructs(const std::string filename);
	bool writeSqls(const std::string filename);
private:
	FILE* openFile(const std::string filename, std::string mode = "rb,ccs=UTF-8");
	size_t countFileData(FILE* fp);
};