/*
*	作为一种低存储消耗的批量bool型开关处理机制
*	只需在枚举（ESWITCH）中添加需要的开关就可以
*
*/
#include <vector>
#include <string>

enum ESWITCH
{
	eswitch1 = 0,
	eswitch2 = 1,
	eswitch3 = 2,
	eswitch4 = 3
};

#define BTRUE 01
#define BITBASE 8
typedef unsigned char UINT8;

const static size_t SWITCH_SIZE = sizeof(UINT8)*BITBASE;

class Switch
{
public:
	Switch(){}
	~Switch(){}

public:
	void openSwitch(ESWITCH e);
	void openSwitch(ESWITCH e, size_t size);
	void setSwitch(ESWITCH e, UINT8 val, size_t size);
	void closeSwitch(ESWITCH e);
	bool stateSwitch(ESWITCH e);
	std::string packSwitch();
	void unpackSwitch(std::string switchs);
private:
	std::vector<UINT8> m_switchs;
};