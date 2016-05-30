#pragma once
#include "person.h"

class CStudent :
	public CPerson
{
public:
	CStudent();
	CStudent(int id,string name,bool sex,Brithday brith,string idcard,int classid);
	virtual ~CStudent();

public:
	int getClassId()            {return m_classId;}
	void setClassId(int classid){m_classId = classid;}

public:
	virtual bool operator==(CStudent &student);
	virtual void operator=(CStudent &student);

protected:
	int m_classId;
};
