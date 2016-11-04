#pragma once
#include "../stdafx.h"

class SysConfMgr:public CSingletion<SysConfMgr>
{
private:
	SysConfMgr();
	~SysConfMgr();

	SINGLETION_FRIEND_CLASS_REGISTER(SysConfMgr);
private:
	struct SColumn{
		std::string name;	//����
		std::string type;	//����
		std::string size;	//����
		bool cnil;	//�Ƿ�ɿ�
		bool unsign;	//�޷���
		bool unique;	//�Ƿ�Ψһ
		bool key;	//�Ƿ�key(����������������)
		SColumn(){
			name = type = size = "";
			cnil = unique = key = unsign = false;
		}
	};
public:
	bool createFromPeiZhi(std::string path);
	map<int, std::string> &GetSqls(){return mTables;}
	vector<std::string> &GetStructs(){return mStructs;}
private:
	bool dealDataBase(xml_node<char> *node);
	bool dealTable(xml_node<char> *node);
	bool dealColumn(xml_node<char> *node, SColumn *column);
	void dbColumn(SColumn *column);
#ifdef _DEBUG
public:
	void printSqls();
#endif
private:
	std::string mTableParam;
	map<int,std::string> mTables;
	vector<std::string> mStructs;
};