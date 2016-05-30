#include "user1.h"
#include "user2.h"
using namespace std;
int main()
{
	userone::CUser UserOne;
	UserOne.SetAge(10);
	cout<<UserOne.GetAge();
	usertwo::CUser UserTwo;
	UserTwo.SetName('M');
	cout<<UserTwo.GetName();
	return 0;
}