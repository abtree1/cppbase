#pragma once
#include "RankListDef.h"
#include "RankListLogic.h"
//伪代码 只是标识使用方法
/**
	按固定时间间隔刷新数据
**/
template<typename T, typename U>
class CRankListSpan {
public:
	CRankListSpan() {
		mHandle.mbHasRank = true;
		//mCompareFunc =
		//mGetFunc = 
	}
	~CRankListSpan() = default;
public:
	//排行榜的总长度 0 为无限长
	void setRankListSize(unsigned int size) {
		mHandle.mRankListSize = size;
	}
	//排行榜刷新时间间隔
	void setTimeSpam(unsigned int timespan) {
		mTimeSpan = timespan;
	}
	template<typename ...Args>
	virtual void update(Args... args) {    //该函数用于更新数据(只是放入更新池 等待刷新)
		//build data
		//update data
		//mHandle.updateRankList()
	}
	virtual void run(unsigned int now) {    //该函数写在循环里面 定时刷新数据
		if (now > mTimeSpan + mLastUpdateTime) {
			deal();
			mLastUpdateTime = now;
		}
	}
	virtual void deal() {     //该函数处理具体的更新操作
		if (mHandle.dirtyRankList()) {
			mHandle.resort(mCompareFunc);
			mHandle.resortKV(mGetFunc);
			//save
		}
	}
	template<typename ...Args>
	virtual void packAndSend(Args... args) {   //该函数用于打包和发送排行榜数据

	}
	virtual void finish() {    //该函数用于排行榜结算
		deal();
		packAndSend();
		//save finish
		mHandle.clear();
	}

	virtual void save() {    //该函数用于存储排行榜

	}

	virtual void load() {  //该函数用于读取排行榜
		//mHandle.mRankList = 
		mHandle.resortKV(mGetFunc);
	}
private:
	CRankListLogic<T, U> mHandle;  //排行榜操作对象句柄
	CompareFunc<T> mCompareFunc;    //排行的规则函数
	GetValueFunc<T, U> mGetFunc;   //获取key值
	unsigned int mTimeSpan{ 0 };       //更新时间
	unsigned int mLastUpdateTime{ 0 }; //上次更新时间
};
