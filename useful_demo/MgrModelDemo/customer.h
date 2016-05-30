#include "rent.h"

class Customer{
public:
	Customer();
	virtual ~Customer(){}
private:
	vector<Rental> m_rental;
	UINT32 m_scales;
	UINT32 m_price;
public:
	void RentGood(Goods* goods,UINT32 days);
protected:
	void AddRental(Rental rental);
};