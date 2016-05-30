#include "Teacher.h"

CTeacher::CTeacher()
{
}

CTeacher::CTeacher(int id,string name,bool sex,Brithday brith,string idcard,string post,string depart)
:CPerson(id,name,sex,brith,idcard)
,m_post(post)
,m_depart(depart)
{

}

CTeacher::~CTeacher()
{
}

bool CTeacher::operator ==(CTeacher &teacher){
	if(teacher.getId() == m_id)
		return true;
	else
		return false;
}

void CTeacher::operator =(CTeacher &teacher){
	this->CPerson::operator =(teacher);
	m_post = teacher.getPost();
	m_depart = teacher.getDepart();
}