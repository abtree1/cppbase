#pragma once
#include "RankListDef.h"
#include "RankListLogic.h"
//α���� ֻ�Ǳ�ʶʹ�÷���
/**
	���̶�ʱ����ˢ������
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
	//���а���ܳ��� 0 Ϊ���޳�
	void setRankListSize(unsigned int size) {
		mHandle.mRankListSize = size;
	}
	//���а�ˢ��ʱ����
	void setTimeSpam(unsigned int timespan) {
		mTimeSpan = timespan;
	}
	template<typename ...Args>
	virtual void update(Args... args) {    //�ú������ڸ�������(ֻ�Ƿ�����³� �ȴ�ˢ��)
		//build data
		//update data
		//mHandle.updateRankList()
	}
	virtual void run(unsigned int now) {    //�ú���д��ѭ������ ��ʱˢ������
		if (now > mTimeSpan + mLastUpdateTime) {
			deal();
			mLastUpdateTime = now;
		}
	}
	virtual void deal() {     //�ú����������ĸ��²���
		if (mHandle.dirtyRankList()) {
			mHandle.resort(mCompareFunc);
			mHandle.resortKV(mGetFunc);
			//save
		}
	}
	template<typename ...Args>
	virtual void packAndSend(Args... args) {   //�ú������ڴ���ͷ������а�����

	}
	virtual void finish() {    //�ú����������а����
		deal();
		packAndSend();
		//save finish
		mHandle.clear();
	}

	virtual void save() {    //�ú������ڴ洢���а�

	}

	virtual void load() {  //�ú������ڶ�ȡ���а�
		//mHandle.mRankList = 
		mHandle.resortKV(mGetFunc);
	}
private:
	CRankListLogic<T, U> mHandle;  //���а����������
	CompareFunc<T> mCompareFunc;    //���еĹ�����
	GetValueFunc<T, U> mGetFunc;   //��ȡkeyֵ
	unsigned int mTimeSpan{ 0 };       //����ʱ��
	unsigned int mLastUpdateTime{ 0 }; //�ϴθ���ʱ��
};
