#include<iostream>
namespace userone
{
	class CUser
	{
	private:
		int m_Age;
	public:
		void SetAge(int age)
		{
			if(m_Age!=age)
				m_Age=age;
		}
		int GetAge()
		{
			return m_Age;
		}
	};
}