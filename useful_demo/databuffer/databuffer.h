#pragma once
#include "stdafx.h"

class DataBuffer{
public:
	DataBuffer();
	DataBuffer(void *buffer,UINT32 bufferSize = BUFFER_SIZE);
	virtual ~DataBuffer();

	bool putData(const void* data,UINT32 dataSize);
	bool putUINT8(UINT8 data);
	bool putUINT16(UINT16 data);
	bool putUINT32(UINT32 data);
	bool putUINT64(UINT64 data);
	bool putINT8(INT8 data);
	bool putINT16(INT16 data);
	bool putINT32(INT32 data);
	bool putINT64(INT64 data);
	bool putBool(bool data);
	bool putChar(char data);
	bool putString(const char* data);
	bool putFloat(float data);
	bool putDouble(double data);

	char* getData(UINT32 dataSize);
	UINT8 getUINT8();
	UINT16 getUINT16();
	UINT32 getUINT32();
	UINT64 getUINT64();
	INT8 getINT8();
	INT16 getINT16();
	INT32 getINT32();
	INT64 getINT64();
	bool getBool();
	char getChar();
	const char* getString();
	float getFloat();
	double getDouble();

	char* getAllData();
	UINT32 getAllDataSize();
	//test
	void resetPos();
private:
	char *m_buffer;      //记录数据数据
	UINT32 m_bufferSize; //记录数据总长度
	char *m_curPos;      //记录当前位置
	UINT32 m_curSize;    //记录剩余长度
};

inline bool DataBuffer::putUINT8(UINT8 data){
	return putData(&data,sizeof(UINT8));
}

inline bool DataBuffer::putUINT16(UINT16 data){
	return putData(&data,sizeof(UINT16));
}

inline bool DataBuffer::putUINT32(UINT32 data){
	return putData(&data,sizeof(UINT32));
}

inline bool DataBuffer::putUINT64(UINT64 data){
	return putData(&data,sizeof(UINT64));
}

inline bool DataBuffer::putINT8(INT8 data){
	return putData(&data,sizeof(INT8));
}

inline bool DataBuffer::putINT16(INT16 data){
	return putData(&data,sizeof(INT16));
}

inline bool DataBuffer::putINT32(INT32 data){
	return putData(&data,sizeof(INT32));
}

inline bool DataBuffer::putINT64(INT64 data){
	return putData(&data,sizeof(INT64));
}

inline bool DataBuffer::putBool(bool data){
	return putData(&data,1);
}

inline bool DataBuffer::putChar(char data){
	return putData(&data,sizeof(char));
}

inline bool DataBuffer::putString(const char *data){
	UINT16 len = strlen(data)+1;
	bool ret = putUINT16(len);
	if(ret)
		return putData(data,len);
	return false;
}

inline bool DataBuffer::putFloat(float data){
	return putData(&data,sizeof(float));
}

inline bool DataBuffer::putDouble(double data){
	return putData(&data,sizeof(double));
}
inline UINT8 DataBuffer::getUINT8(){
	const char* data1 = getData(sizeof(UINT8));
	return *(const UINT8*)data1;
}

inline UINT16 DataBuffer::getUINT16(){
	const char* data1 = getData(sizeof(UINT16));
	return *(const UINT16*)data1;
}

inline UINT32 DataBuffer::getUINT32(){
	const char* data1 = getData(sizeof(UINT32));
	return *(const UINT32*)data1;
}

inline UINT64 DataBuffer::getUINT64(){
	const char* data1 = getData(sizeof(UINT64));
	return *(const UINT64*)data1;
}

inline INT8 DataBuffer::getINT8(){
	const char* data1 = getData(sizeof(INT8));
	return *(const INT8*)data1;
}

inline INT16 DataBuffer::getINT16(){
	const char* data1 = getData(sizeof(INT16));
	return *(const INT16*)data1;
}

inline INT32 DataBuffer::getINT32(){
	const char* data1 = getData(sizeof(INT32));
	return *(const INT32*)data1;
}

inline INT64 DataBuffer::getINT64(){
	const char* data1 = getData(sizeof(INT64));
	return *(const INT64*)data1;
}

inline bool DataBuffer::getBool(){
	return 0 != getUINT8();
}

inline char DataBuffer::getChar(){
	const char* data1 = getData(sizeof(char));
	return *(const char*)data1;
}

inline const char *DataBuffer::getString(){
	UINT16 size = getUINT16(); 

	return getData(size);
}

inline float DataBuffer::getFloat(){
	const char* data1 = getData(sizeof(float));
	return *(const float*)data1;
}

inline double DataBuffer::getDouble(){
	const char* data1 = getData(sizeof(double));
	return *(const double*)data1;
}