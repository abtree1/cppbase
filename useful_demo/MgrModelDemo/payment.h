#pragma once
#include "public.h"

class Payment{
public:
	Payment(){}
	virtual ~Payment(){}
	virtual UINT32 CountPrice(UINT32 price,UINT32 days) = 0;
	virtual UINT32 CountScales(UINT32 price,UINT32 days) = 0;
	virtual GoodsType GetType() = 0;
};

class NewPayment:public Payment{
public:
	virtual UINT32 CountPrice(UINT32 price,UINT32 days);
	virtual UINT32 CountScales(UINT32 price,UINT32 days);
public:
	virtual GoodsType GetType(){return GOODS_NEW;}
};

class ScalesPayment:public Payment{
public:
	virtual UINT32 CountPrice(UINT32 price,UINT32 days);
	virtual UINT32 CountScales(UINT32 price,UINT32 days);
public:
	virtual GoodsType GetType(){return GOODS_SCALE;}
};

class NormalPayment:public Payment{
public:
	virtual UINT32 CountPrice(UINT32 price,UINT32 days);
	virtual UINT32 CountScales(UINT32 price,UINT32 days){return 0;}
public:
	virtual GoodsType GetType(){return GOODS_NORMAL;}
};