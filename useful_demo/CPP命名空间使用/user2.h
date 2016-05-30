#include<iostream>
namespace usertwo
{
	class CUser
	{
	private:
		char m_Name;
	public:
		void SetName(char name)
		{
			m_Name=name;
		}
		char GetName()
		{
			return m_Name;
		}
	};
}