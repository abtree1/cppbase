#include "Student.h"

CStudent::CStudent()
{
}

CStudent::CStudent(int id,string name,bool sex,Brithday brith,string idcard,int classid)
:CPerson(id,name,sex,brith,idcard)
,m_classId(classid){

}

CStudent::~CStudent()
{
}

bool CStudent::operator ==(CStudent &student){
	if(student.getId() == m_id)
		return true;
	else
		return false;
}

void CStudent::operator =(CStudent &student){
	this->CPerson::operator =(student);
	m_classId = student.getClassId();
}