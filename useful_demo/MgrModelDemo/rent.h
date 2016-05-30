#include "goods.h"

class Rental{
public:
	Rental(Goods* goods,UINT32 days);
	virtual ~Rental(){}
private:
	Goods* m_goods;
	UINT32 m_days;
public:
	UINT32 CountScales();
	UINT32 CountPrice();
};