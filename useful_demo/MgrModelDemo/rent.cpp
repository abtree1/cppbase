#include "rent.h"

Rental::Rental(Goods* goods,UINT32 days):m_goods(goods){
	m_days = days;
}

UINT32 Rental::CountPrice(){
	//UINT32 price = 0;
	//switch(m_goods.GetGoodsType())
	//{
	//case GOODS_NEW:
	//	price = m_goods.GetPrice()*m_days*2;  //新物品上架，2倍租金
	//	break;
	//case GOODS_SCALE:
	//case GOODS_NORMAL:
	//	price = m_goods.GetPrice()*m_days;
	//	break;
	//}

	//return price;

	return m_goods->CountPrice(m_days);
}

UINT32 Rental::CountScales(){
	/*UINT32 scales = 0;
	switch(m_goods.GetGoodsType()){
		case GOODS_NEW:
			scales = m_days*m_goods.GetPrice()*0.1*2;
			break;
		case GOODS_SCALE:
			scales = m_days*m_goods.GetPrice()*0.1;
			break;
	}
	return scales;*/
	return m_goods->CountScales(m_days);
}