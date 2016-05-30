#pragma once
#include "person.h"

class CTeacher :
	public CPerson
{
public:
	CTeacher();
	CTeacher(int id,string name,bool sex,Brithday brith,string idcard,string post,string depart);
	~CTeacher();

public:
	string getPost()  {return m_post;}
	string getDepart(){return m_depart;}

	void setPost(string post)    {m_post = post;}
	void setDepart(string depart){m_depart = depart;}

public:
	virtual bool operator==(CTeacher &teacher);
	virtual void operator=(CTeacher &teacher);

protected:
	string m_post;    //职务
	string m_depart;  //部门
};
