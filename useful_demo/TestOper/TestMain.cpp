#include "Student.h"
#include "Teacher.h"

int main(){
	Brithday bri(2001,1,23);
	//CPerson per1;
	//CPerson per2(1,"123",true,bri,"123");

//	//CTeacher per2(1,"姓名",true,bri,"身份证","职务","部门1");
	//CTeacher per1;

	CStudent per2(1,"123",true,bri,"123",1);
	CStudent per1;

	per1 = per2;

	cout << per1.getId() << ":" << per1.getName() << ":" << per1.getBrithday().year <<":"
		<< per1.getBrithday().month << ":" << per1.getBrithday().day << ":"
		<<per1.getIdcard() << ":" << per1.getSex()<<":" << per1.getVisible()<<":"
		<< per1.getClassId()<<":"<< endl;
	cout << (per1 == per2) << endl;
}