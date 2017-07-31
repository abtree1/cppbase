#include <iostream>
#include "RankList.h"
using namespace std;

using u32 = unsigned int;

struct SRankData {
	u32 rank{ 0 };
	u32 guid{ 0 };
	u32 power{ 0 };

	SRankData &operator=(const SRankData &lcx);
};

SRankData &SRankData::operator=(const SRankData& lcx) {
	this->guid = lcx.guid;
	this->power = lcx.power;
	return *this;
}

int main()
{
	CRankListSort<SRankData, u32> mRankListHandle;
	CompareFunc<SRankData> mHandleFuncPtr = [](const SRankData& a, const SRankData& b)->int {
		if (a.power > b.power)
			return 1;
		else if (a.power < b.power)
			return -1;
		else
			return 0;
	};
	GetValueFunc<SRankData, u32> mGetFuncPtr = [](const SRankData& a)->u32 {
		return a.guid;
	};
	mRankListHandle.hasRank = true;
	mRankListHandle.RankListSize = 100;

	u32 guid, power;
	while (true) {
		std::cin >> guid >> power;
		if (guid == 0)
			break;
		if (guid == 1 && power == 0) {
			mRankListHandle.dirtyRankList();
			mRankListHandle.resort(mHandleFuncPtr);
			mRankListHandle.resortKV(mGetFuncPtr);
			for (auto &itp : mRankListHandle.mRankList) {
				cout << itp.rank << " "
					<< itp.guid << " "
					<< itp.power << " "
					<< endl;
			}
		}
		else {
			SRankData data;
			data.guid = guid;
			data.power = power;
			mRankListHandle.updateRankList(data, data.guid);
		}
	/*	int from = mRankListHandle.mRankList.size();
		auto it = mRankListHandle.mRankListKV.find(guid);
		if (it != mRankListHandle.mRankListKV.end()) {
			assert(mRankListHandle.mRankList[it->second].guid == guid);
			from = it->second;
			mRankListHandle.mRankList[from].power = power;
		}
		else {
			SRankData data;
			data.guid = guid;
			data.power = power;
			data.rank = from;
			mRankListHandle.mRankList.push_back(data);
		}
		int to = mRankListHandle.getRankTo(from, mHandleFuncPtr);
		mRankListHandle.moveRankList(from, to, mGetFuncPtr);*/
		//mRankListHandle.sortRankList(from, mHandleFuncPtr);
		/*for (auto &itp : mRankListHandle.mRankList) {
			cout << itp.rank << " "
				<< itp.guid << " "
				<< itp.power << " "
				<< endl;
		}*/
	}

    return 0;
}

