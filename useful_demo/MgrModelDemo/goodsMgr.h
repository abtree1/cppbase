#include "goods.h"

typedef map<string,Goods*> GoodsMap;

class GoodsMgr{
public:
	GoodsMgr(){}
	~GoodsMgr();
public:
	void addGoods(string name,UINT32 price,GoodsType type);
	void dropGoods(string name);
	void updateGoods(string name,UINT32 price,GoodsType type);
	Goods* findGoods(string name);
/*与数据库交互
public:  
	DataBuffer* packToDB(){}
	void unPackFromDB(DataBuffer* msg){}
*/
/*与文件交互
public:  
	void initFromFile(char* data){}
*/
private:
	GoodsMap m_goodsMap;
};