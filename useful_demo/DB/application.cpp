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
	SysConfMgr::GetInstance()->saveSqls2file("E:/cpp/cppbase/useful_demo/DB/db_sql.sqlx");
	SysConfMgr::GetInstance()->saveStructs2File("E:/cpp/cppbase/useful_demo/DB/db_s.h");
	destory();
	return 0;
}