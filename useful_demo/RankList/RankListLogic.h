#pragma once
template<typename T>
using CompareFunc = int(*)(const T&, const T&);
template<typename T, typename U>
using GetValueFunc = U(*)(const T&);

template<typename T, typename U>
class CRankListLogic {
public:
	int getRankTo(int from, CompareFunc<T> func) {
		int size = mRankList.size();
		int to = from;
		if (from > 0 && func(mRankList[from], mRankList[from - 1]) > 0) {
			//��ǰ�ƶ�
			to = 0;
			for (int i = from - 2; i >= 0; --i) {
				if (func(mRankList[from], mRankList[i]) <= 0) {
					to = i + 1;
					break;
				}
			}
		}
		else if (from < size - 1 && func(mRankList[from], mRankList[from + 1]) <= 0) {
			//����ƶ�
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
		if (mRankListSize > 0) {
			while (mRankList.size() > mRankListSize) {
				mRankListKV.erase(func(mRankList[mRankList.size() - 1]));
				mRankList.pop_back();
			}
		}
	}

	void puahBack(T& data, GetValueFunc<T, U> func) {
		if (mbHasRank)
			data.rank = mRankList.size();
		mRankList.push_back(data);
		mRankListKV[func(data)] = mRankList.size() - 1;
	}

	/*void sortRankList(int from, CompareFunc<T> func) {
	int to = getRankTo(from, func);
	moveRankList(from, to);
	}*/

	void updateRankList(T& data, U& key) {
		mRankListHelp[key] = data;
	}

	//hasRank ��ʶ��RankData���Ƿ���rank�ֶ�
	bool dirtyRankList() {
		if (mRankListHelp.empty())
			return false;
		for (auto &it : mRankListHelp) {
			auto itkv = mRankListKV.find(it.first);
			if (itkv != mRankListKV.end()) {
				//assert(mRankList[itkv->second].guid == itkv->first);
				mRankList[itkv->second] = it.second;
			}
			else {
				if (mbHasRank)
					it.second.rank = mRankList.size();
				mRankList.push_back(it.second);
			}
		}
		mRankListHelp.clear();
		return true;
	}

	void resort(CompareFunc<T> func, bool resetRank = false) {
		auto compareFuncPtr = [func](const T& a, const T& b) {
			if (func(a, b) > 0)
				return true;
			return false;
		};
		std::sort(mRankList.begin(), mRankList.end(), compareFuncPtr);
		if (mRankListSize > 0 && mRankList.size() > mRankListSize)
			mRankList._Pop_back_n(mRankList.size() - mRankListSize);
		//�����rank�ֶζ�����Ҫǿ������
		if (mbHasRank && resetRank) {
			int pos = 0;
			for (auto &it : mRankList) {
				it.rank = pos;
				++pos;
			}
		}
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
		mRankListKV.clear();
		int pos = 0;
		for (auto &it : mRankList) {
			mRankListKV[func(it)] = pos;
			++pos;
		}
	}

	int getRank(U key) {
		auto it = mRankListKV.find(key);
		if (it == mRankListKV.end())
			return -1;
		return it->second;
	}

	void clear() {
		mRankList.clear();
		mRankListHelp.clear();
		mRankListKV.clear();
	}
public:
	vector<T> mRankList;    //���а�����
	map<U, int> mRankListKV;  //���ڱ�ʶKey��rank��Ӧ
	map<U, T> mRankListHelp;  //�Ǽ�ʱ���еĸ������л���
							  //�Ƿ���rank�ֶ�
	bool mbHasRank{ false };
	//���а����󳤶�
	int mRankListSize{ 0 };
};