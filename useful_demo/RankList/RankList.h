#pragma once
#include <vector>
#include <map>
#include <assert.h>
#include <algorithm> 

template<typename T>
using CompareFunc = int(*)(const T&, const T&);
template<typename T, typename U>
using GetValueFunc = U(*)(const T&);

template<typename T, typename U>
class CRankListSort {
public:
	int getRankTo(int from, CompareFunc<T> func) {
		int size = mRankList.size();
		int to = from;
		if (from > 0 && func(mRankList[from], mRankList[from - 1]) > 0) {
			//向前移动
			to = 0;
			for (int i = from - 2; i >= 0; --i) {
				if (func(mRankList[from], mRankList[i]) <= 0) {
					to = i + 1;
					break;
				}
			}
		}
		else if (from < size - 1 && func(mRankList[from], mRankList[from + 1]) <= 0) {
			//向后移动
			to = size - 1;
			for (int i = from + 1; i < size; ++i) {
				if (func(mRankList[from], mRankList[i]) > 0) {
					to = i - 1;
					break;
				}
			}
		}
		return to;
	}

	void moveRankList(int from, int to, GetValueFunc<T, U> func) {
		T data = mRankList[from];
		if (from > to) {
			for (int i = from; i > to; --i) {
				mRankList[i] = mRankList[i - 1];
				mRankListKV[func(mRankList[i])] = i;
			}
			mRankList[to] = data;
			mRankListKV[func(data)] = to;
		}
		else if (from < to) {
			for (int i = from; i < to; ++i) {
				mRankList[i] = mRankList[i + 1];
				mRankListKV[func(mRankList[i])] = i;
			}
			mRankList[to] = data;
			mRankListKV[func(data)] = to;
		}
		while (mRankList.size() > RankListSize) {
			mRankListKV.erase(func(mRankList[mRankList.size() - 1]));
			mRankList.pop_back();
		}
	}

	/*void sortRankList(int from, CompareFunc<T> func) {
		int to = getRankTo(from, func);
		moveRankList(from, to);
	}*/

	void updateRankList(T& data, U& key) {
		mRankListHelp[key] = data;
	}

	//hasRank 标识在RankData中是否有rank字段
	void dirtyRankList() {
		for (auto &it : mRankListHelp) {
			auto itkv = mRankListKV.find(it.first);
			if (itkv != mRankListKV.end()) {
				assert(mRankList[itkv->second].guid == itkv->first);
				mRankList[itkv->second] = it.second;
			}
			else {
				if (hasRank)
					it.second.rank = mRankList.size();
				mRankList.push_back(it.second);
			}
		}
	}

	void resort(CompareFunc<T> func) {
		auto compareFuncPtr = [func](const T& a, const T& b) {
			if (func(a, b) > 0)
				return true;
			return false;
		};
		std::sort(mRankList.begin(), mRankList.end(), compareFuncPtr);
		if (mRankList.size() > RankListSize)
			mRankList._Pop_back_n(mRankList.size() - RankListSize);
		/*vector<T> oldlist = list;
		list.clear();
		int from = 0;
		for (auto &it : oldlist) {
		from = list.size();
		list.push_back(it);
		sortRankList(list, from, func);
		}*/
	}
	void resortKV(GetValueFunc<T, U> func) {
		int pos = 0;
		for (auto &it : mRankList) {
			mRankListKV[func(it)] = pos;
			++pos;
		}
	}

	int &getRank(U key) {
		auto it = mRankListKV.find(key);
		if (it == mRankListKV.end())
			return -1;
		return it->second;
	}
public:
	vector<T> mRankList;    //排行榜数据
	map<U, int> mRankListKV;  //用于标识Key和rank对应
	map<U, T> mRankListHelp;  //非即时排行的辅助排行缓存
	//是否有rank字段
	bool hasRank{ false };
	//排行榜的最大长度
	int RankListSize{ 0 };
};