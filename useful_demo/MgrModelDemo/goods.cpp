#include "goods.h"

Goods::Goods(UINT32 price,string name,GoodsType type){
	m_price = price;
	m_name = name;
	pPayment = NULL;
	m_visible = true;
	SetGoodsType(type);
}

Goods& Goods::operator =(Goods goods){
	if(this == &goods)
		return *this;

	m_price = goods.GetPrice();
	m_name = goods.GetName();
	pPayment = NULL;
	m_visible = goods.GetVisible();
	SetGoodsType(goods.GetGoodsType());
	return *this;
}

Goods::~Goods(){
	if(pPayment)
		delete pPayment;
}

void Goods::SetGoodsType(GoodsType type){
	if(pPayment)
		delete pPayment;

	switch(type){
		case GOODS_NEW:
			pPayment = new NewPayment();
			break;
		case GOODS_NORMAL:
			pPayment = new NormalPayment();
			break;
		case GOODS_SCALE:
			pPayment = new ScalesPayment();
			break;
	}
}

GoodsType Goods::GetGoodsType(){
	return pPayment->GetType();
}

UINT32 Goods::CountPrice(UINT32 days){
	//UINT32 price = 0;
	//switch(m_goodsType)
	//{
	//case GOODS_NEW:
	//	price = m_price*days*2;  //新物品上架，2倍租金
	//	break;
	//case GOODS_SCALE:
	//case GOODS_NORMAL:
	//	price = m_price*days;
	//	break;
	//}

	//return price;
	if(!pPayment)
		__asm{int 3}

	return pPayment->CountPrice(m_price,days);
}

UINT32 Goods::CountScales(UINT32 days){
	/*UINT32 scales = 0;
	switch(m_goodsType){
		case GOODS_NEW:
			scales = days*m_price*0.1*2;
			break;
		case GOODS_SCALE:
			scales = days*m_price*0.1;
			break;
	}
	return scales;*/
	if(!pPayment)
		__asm{int 3}

	return pPayment->CountScales(m_price,days);
}