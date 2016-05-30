#pragma once
#include "payment.h"

class Goods{
public:
	Goods(UINT32 price,string name,GoodsType type = GOODS_NEW);
	Goods& operator =(Goods goods);
	virtual ~Goods();
private:
	UINT32 m_price;
	string m_name;
	bool m_visible;
	//GoodsType m_goodsType;
	Payment *pPayment;
public:
	void SetPrice(UINT32 price)	{m_price = price;}
	UINT32 GetPrice()			{return m_price;}
	void SetName(string name)	{m_name = name;}
	string GetName()			{return m_name;}
	void SetVisible(bool vis)	{m_visible = vis;}
	bool GetVisible()			{return m_visible;}
	void SetGoodsType(GoodsType type);//{m_goodsType = type;}
	GoodsType GetGoodsType();	//{return m_goodsType;}
public:
	UINT32 CountPrice(UINT32 days);
	UINT32 CountScales(UINT32 days);
};