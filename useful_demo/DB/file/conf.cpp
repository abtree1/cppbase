#include "conf.h"

CReadConf::CReadConf()
{
}

CReadConf::~CReadConf()
{
}

FILE* CReadConf::openFile(const string filename, string mode){
	FILE* fp = nullptr;
	if(0 != fopen_s(&fp, filename.c_str(), mode.c_str())){
		printf_s("open file(%s)(%s) error", filename.c_str(), mode.c_str());
		return nullptr;
	}
	return fp;
}

bool CReadConf::readAllData_s(const std::string filename, std::string &out){
	FILE* fp = openFile(filename);

	if(nullptr == fp){
		printf_s("open file(%s) error", filename.c_str());
		return false;
	}

	size_t size = countFileData(fp);
	char *buf = new char[size + 1];
	if(fread(buf, size, 1, fp) != 1){
		delete [] buf;
		printf_s("read file data error \n");
		fclose(fp);
		return false;
	}
	buf[size] = '\0';
	//文件编码验证
	/*if ((unsigned char)buf[0]!=0xEF || (unsigned char)buf[1]!=0xBB){
		delete [] buf;
		printf_s("file not code with utf8 \n");
		fclose(fp);
		return 0;
	}*/
	out = string(buf);
	delete [] buf;
	fclose(fp);

	return true;
}

size_t CReadConf::countFileData(FILE* fp){
	if(nullptr == fp || NULL == fp) return 0;
	fseek(fp, 0, SEEK_END);
	size_t size = ftell(fp);
	rewind(fp);
	return size;
}

bool CReadConf::writeStructs(const std::string filename){
	FILE* fp = openFile(filename, "w");
	if(nullptr == fp){
		printf_s("open file(%s) error", filename.c_str());
		return false;
	}

	vector<std::string> strs = SysConfMgr::GetInstance()->GetStructs();
	for(std::string s : strs){
		fputs(s.c_str(), fp);
	}

	fflush(fp);
	fclose(fp);
	return true;
}

bool CReadConf::writeSqls(const std::string filename){
	FILE* fp = openFile(filename, "w");
	if(nullptr == fp){
		printf_s("open file(%s) error", filename.c_str());
		return false;
	}

	map<int, std::string> strs = SysConfMgr::GetInstance()->GetSqls();
	auto it = strs.begin();
	for(; it != strs.end(); ++it){
		fprintf(fp,"%d->%s",it->first,it->second.c_str());
	}

	fflush(fp);
	fclose(fp);
	return true;
}