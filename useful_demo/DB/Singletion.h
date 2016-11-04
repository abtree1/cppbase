#pragma once
/************************************************************************/
/* @单件模板类                                                            
/* 1.单件类应该public继承此类，并构造函数和析构函数设为私有
/* 2.拷贝构造，= 为私有
/* 3.声明处FRIEND_CLASS_REGISTER(T)
/************************************************************************/
template<typename T>
class CSingletion
{
public:
	static T*	GetInstance()
	{
		return mInstance;
	}

	static bool CreateInstance()
	{
		if (!mInstance)
		{
			mInstance = new T;
		}
		return mInstance != 0;
	}
	static void DestroyInstance()
	{
		if (mInstance)
		{
			delete mInstance;
			mInstance = 0;
		}
	}
protected:
	CSingletion(void) {}
	virtual ~CSingletion(void) {}

private:
	static T*	mInstance;
};

#define SINGLETION_FRIEND_CLASS_REGISTER(T) friend class CSingletion<T>;

template<typename T>
T* CSingletion<T>::mInstance = 0;

/************************************************************************
	@单件类封装                                                           
	1.应当声明 构造，析构，拷贝构造，= 为私有
	2.添加DECLARE_SINGLETION(cls)到声明处
	3.添加IMPLEMENT_SINGLETION(cls)到定义处
/************************************************************************/
#define SIMPLEMENT_SINGLETION(cls)\
	public:\
		static cls* CreateInstance()\
		{\
			static cls mCls;\
			return &mCls;\
		}

#define DECLARE_SINGLETION(cls)\
	private:\
		static cls* mInstance;\
	public:\
		static bool CreateInsatance()\
		{\
			if (!mInstance)\
				mInstance = new cls;\
			return 0 != mInstance;\
		}\
		static void DestroyInstance()\
		{\
			if (mInstance)\
				delete mInstance;\
			mInstance = 0;\
		}\
		static cls* GetInstance() { return mInstance; }

#define ImPLEMENT_SINGLETION(cls)\
	cls* cls::mInstance = 0;