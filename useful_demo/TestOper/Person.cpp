#include "Person.h"

CPerson::CPerson()
{
}

CPerson::CPerson(int id,string name,bool sex,Brithday brith,string idcard)
:m_id(id)
,m_name(name)
,m_sex(sex)
,m_brith(brith)
,m_idcard(idcard)
,m_visible(true)
{
}

CPerson::~CPerson(void)
{
}

bool CPerson::operator ==(CPerson &person){
	if(m_id == person.getId())
		return true;
	else
		return false;
}

void CPerson::operator =(CPerson &person){
	m_id = person.getId();
	m_brith = person.getBrithday();
	m_idcard = person.getIdcard();
	m_name = person.getName();
	m_sex = person.getSex();
	m_visible = person.getVisible();
}