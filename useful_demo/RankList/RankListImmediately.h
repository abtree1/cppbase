#pragma once
//伪代码 只是标识使用方法
template<typename T, typename U>
class CRankListImmediately {
public:
	CRankListImmediately() {
		mHandle.mbHasRank = true;
	}
	~CRankListImmediately() = default;
public:
	void setTimeSpan(unsigned int timespan) { mTimeSpan = timespan; }
	void setRankListSize(unsigned int size) { mHandle.mRankListSize = size; }
	template<typename ...Args>
	virtual void update(Args... args) {
		//int from = mHandle.mRankList.size();
		//auto it = mHandle.mRankListKV.find(key);
		//if (it != mHandle.mRankListKV.end()) {
		//	//update it data
		//}
		//else {
		//	//build a new data
		//	mHandle.puahBack(data, mGetVFunc);
		//}
		//int to = mHandle.getRankTo(from, mCompareFunc);
		//mHandle.moveRankList(from, to, mGetVFunc);
	}

	template<typename ...Args>
	virtual void packAndSend(Args... args) {

	}

	virtual void run(unsigned int now) {
		if (now > mLastUpdateTime + mTimeSpan) {
			save();
			mLastUpdateTime = now;
		}
	}

	virtual void save() {

	}

	virtual void load() {

	}
private:
	CRankListLogic<T, U> mHandle;
	CompareFunc<T> mCompareFunc;
	GetValueFunc<T, U> mGetVFunc;
	unsigned int mTimeSpan{ 0 };
	unsigned int mLastUpdateTime{ 0 };
};