#include "stdafx.h"

void init(){
	CReadConf::CreateInstance();
	SysConfMgr::CreateInstance();
}

void destory(){
	CReadConf::DestroyInstance();
	SysConfMgr::DestroyInstance();
}

int main(){
	init();
	SysConfMgr::GetInstance()->createFromPeiZhi("E:/cpp/cppbase/useful_demo/DB/db.xml");
#ifdef _DEBUG
	SysConfMgr::GetInstance()->printSqls();
#endif
	CReadConf::GetInstance()->writeStructs("E:/cpp/cppbase/useful_demo/DB/db_s.h");
	CReadConf::GetInstance()->writeSqls("E:/cpp/cppbase/useful_demo/DB/db_sql.sqlx");
	destory();
	return 0;
}