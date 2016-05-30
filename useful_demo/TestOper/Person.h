#pragma once
#include <string>
#include <iostream>

using namespace std;

struct Brithday
{
	unsigned short year;
	unsigned short month:4;
	unsigned short day:5;

	Brithday(){}

	Brithday(unsigned short y,unsigned short m,unsigned short d):year(y),month(m),day(d){}
	
	virtual void operator=(Brithday &brith){
		year = brith.year;
		month = brith.month;
		day = brith.day;
	}
};

class CPerson
{
public:
	CPerson();
	CPerson(int id,string name,bool sex,Brithday brith,string idcard);
	virtual ~CPerson();

public:
	int getId()           {return m_id;}
	string getName()      {return m_name;}
	bool getSex()         {return m_sex;}
	string getIdcard()    {return m_idcard;}
	bool getVisible()     {return m_visible;}
	Brithday getBrithday(){return m_brith;}

	void setId(int id)              {m_id = id;  }
	void setName(string name)       {m_name = name;}
	void setSex(bool sex)           {m_sex = sex;}
	void setBrithday(Brithday brith){m_brith = brith;}
	void setIdcard(string idcard)   {m_idcard = idcard;}
	void setVisible(bool visible)   {m_visible = visible;}

public:
	virtual bool operator==(CPerson &person);
	virtual void operator=(CPerson &person);

protected:
	int m_id;
	string m_name;
	bool m_sex;
	Brithday m_brith;
	string m_idcard;
	bool m_visible;
};
