#include "stdafx.h"
#include "databuffer.h"

DataBuffer::DataBuffer(){
	m_bufferSize = BUFFER_SIZE;
	m_buffer = new char[m_bufferSize];
	m_curPos = m_buffer;
	m_curSize = m_bufferSize;
}

DataBuffer::DataBuffer(void* buffer,UINT32 bufferSize){
	m_buffer = new char[BUFFER_SIZE];
	memcpy(m_buffer,buffer,bufferSize);
	m_bufferSize = bufferSize;
	m_curPos = m_buffer;
	m_curSize = m_bufferSize;
}

DataBuffer::~DataBuffer(){
	delete m_buffer;
}

bool DataBuffer::putData(const void* data,UINT32 dataSize){
	if(m_curSize >= dataSize){
		memcpy(m_curPos,data,dataSize);
		m_curPos += dataSize;
		m_curSize -= dataSize;

		return true;
	}

	return false;
}

char* DataBuffer::getData(UINT32 dataSize){
	if(m_curSize < dataSize){
		return NULL;
	}

	char* const pData = m_curPos;

	m_curPos += dataSize;
	m_curSize -= dataSize;

	return pData;
}

char* DataBuffer::getAllData(){
	return (char*)m_buffer;
}

UINT32 DataBuffer::getAllDataSize(){
	return m_bufferSize - m_curSize;
}

void DataBuffer::resetPos(){
	m_curPos = m_buffer;
	m_curSize = m_bufferSize;
}