#include "payment.h"

UINT32 NewPayment::CountPrice(UINT32 price,UINT32 days){
	return (UINT32)price*days*2;  //新物品上架，2倍租金
}

UINT32 NewPayment::CountScales(UINT32 price,UINT32 days){
	return (UINT32)days*price*0.1*2;
}

UINT32 ScalesPayment::CountPrice(UINT32 price,UINT32 days){
	return (UINT32)price*days;
}

UINT32 ScalesPayment::CountScales(UINT32 price,UINT32 days){
	return (UINT32)days*price*0.1;
}

UINT32 NormalPayment::CountPrice(UINT32 price,UINT32 days){
	return (UINT32)price*days;
}