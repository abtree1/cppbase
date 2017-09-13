#pragma once
#include "RankListDef.h"
#include "RankListLogic.h"
//伪代码 只是标识使用方法
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
	void setRankListSize(unsigned int size) {
		mHandle.mRankListSize = size;
	}
	void setTimeSpam(unsigned int timespan) {
		mTimeSpan = timespan;
	}
	template<typename ...Args>
	virtual void update(Args... args) {
		//build data
		//update data
		//mHandle.updateRankList()
	}
	virtual void run(unsigned int now) {
		if (now > mTimeSpan + mLastUpdateTime) {
			deal();
			mLastUpdateTime = now;
		}
	}
	virtual void deal() {
		if (mHandle.dirtyRankList()) {
			//mHandle.resort(mCompareFunc);
			//mHandle.resortKV(mGetFunc);
			//save
		}
	}
	template<typename ...Args>
	virtual void packAndSend(Args... args) {

	}
	virtual void finish() {
		//deal();
		//packAndSend();
		//save finish
		//mHandle.clear();
	}

	virtual void save() {

	}

	virtual void load() {

	}
private:
	CRankListLogic<T, U> mHandle;
	//CompareFunc<T> mCompareFunc;
	//GetValueFunc<T, U> mGetFunc;
	unsigned int mTimeSpan{ 0 };       //更新时间
	unsigned int mLastUpdateTime{ 0 }; //上次更新时间
};
