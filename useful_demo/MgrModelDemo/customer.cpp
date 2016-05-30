#include "customer.h"

Customer::Customer(){
	m_scales = 0;
	m_price = 0;
}

void Customer::AddRental(Rental rental){
	m_rental.push_back(rental);
}

void Customer::RentGood(Goods* goods,UINT32 days){
	Rental rental(goods,days);
	m_scales += rental.CountScales();
	m_price += rental.CountPrice();
	AddRental(rental);

	cout << "租赁成功！累计消费：" <<m_price<<"累计积分："<<m_scales<<endl; 
}