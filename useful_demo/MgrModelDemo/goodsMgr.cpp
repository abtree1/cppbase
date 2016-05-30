#include "goodsMgr.h"
#include "util.h"

GoodsMgr::~GoodsMgr(){
	GoodsMap::iterator it = m_goodsMap.begin();
	if (it != m_goodsMap.end()){
		SAFE_DELETE(it->second);
		m_goodsMap.erase(it);
	}
}

void GoodsMgr::addGoods(string name,UINT32 price,GoodsType type){
	if (m_goodsMap.find(name) == m_goodsMap.end())
	{
		Goods *goods = new Goods(price,name,type);
		if(goods)
			m_goodsMap.insert(make_pair(name.c_str(),goods));
	}
}

void GoodsMgr::dropGoods(string name){
	GoodsMap::iterator it = m_goodsMap.find(name);
	if (it != m_goodsMap.end()){
		it->second->SetVisible(false); //此处只将其标为不可见
	}
}

void GoodsMgr::updateGoods(string name,UINT32 price,GoodsType type){
	GoodsMap::iterator it = m_goodsMap.find(name);
	if (it != m_goodsMap.end()){
		Goods *goods = it->second;
		goods->SetName(name.c_str());
		goods->SetPrice(price);
		goods->SetGoodsType(type);
		goods->SetVisible(true);
	}
}

Goods* GoodsMgr::findGoods(string name){
	GoodsMap::iterator it = m_goodsMap.find(name);
	if (it != m_goodsMap.end() && it->second->GetVisible()){
		return it->second;
	}

	return NULL;
}