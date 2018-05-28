#pragma once
#include <iostream>
using namespace std;

typedef unsigned int u32;
class ULarge {
public:
	//Ĭ�Ϲ��캯��
	ULarge() = default;
	//U32���캯��
	ULarge(u32 val);
	ULarge(u32 pow, u32 rem);
	//string ���캯��
	ULarge(string val);
	//�������캯��
	ULarge(const ULarge& other);
public:
	//��ֵ����
	ULarge &operator=(const ULarge &other);
	//+=
	ULarge &operator+=(const u32 val);
	ULarge &operator+=(const ULarge &other);
	//-=
	ULarge &operator-=(const u32 val);
	ULarge &operator-=(const ULarge &other);
	//[]
	u32 operator[](bool pow);
public:
	friend ULarge operator+(const ULarge& lcx, const u32 val);
	friend ULarge operator+(const ULarge& lcx, const ULarge& rcx);
	friend ULarge operator-(const ULarge& lcx, const u32 val);
	friend ULarge operator-(const ULarge& lcx, const ULarge& rcx);
	friend double operator/(const ULarge& lcx, const u32 val);
	friend double operator/(const ULarge& lcx, const ULarge& rcx);
public:
	friend bool operator==(const ULarge& lcx, const u32 val);
	friend bool operator==(const ULarge& lcx, const ULarge& rcx);
	friend bool operator!=(const ULarge& lcx, const u32 val);
	friend bool operator!=(const ULarge& lcx, const ULarge& rcx);
public:
	friend bool operator>(const ULarge& lcx, const u32 val);
	friend bool operator>(const ULarge& lcx, const ULarge& rcx);
	friend bool operator>=(const ULarge& lcx, const u32 val);
	friend bool operator>=(const ULarge& lcx, const ULarge& rcx);
	friend bool operator<(const ULarge& lcx, const u32 val);
	friend bool operator<(const ULarge& lcx, const ULarge& rcx);
	friend bool operator<=(const ULarge& lcx, const u32 val);
	friend bool operator<=(const ULarge& lcx, const ULarge& rcx);
private:
	u32 _rem{ 0 };  //����
	u32 _pow{ 0 };  //����
public:
	const static u32 _max{ 2100000000 };
};

extern ULarge operator ""_un(const char* col, size_t n);
extern ULarge operator+(const ULarge& lcx, const u32 val);
extern ULarge operator+(const ULarge& lcx, const ULarge& rcx);
extern ULarge operator-(const ULarge& lcx, const u32 val);
extern ULarge operator-(const ULarge& lcx, const ULarge& rcx);
extern double operator/(const ULarge& lcx, const u32 val);
extern double operator/(const ULarge& lcx, const ULarge& rcx);

extern bool operator==(const ULarge& lcx, const u32 val);
extern bool operator==(const ULarge& lcx, const ULarge& rcx);
extern bool operator!=(const ULarge& lcx, const u32 val);
extern bool operator!=(const ULarge& lcx, const ULarge& rcx);

extern bool operator>(const ULarge& lcx, const u32 val);
extern bool operator>(const ULarge& lcx, const ULarge& rcx);
extern bool operator>=(const ULarge& lcx, const u32 val);
extern bool operator>=(const ULarge& lcx, const ULarge& rcx);
extern bool operator<(const ULarge& lcx, const u32 val);
extern bool operator<(const ULarge& lcx, const ULarge& rcx);
extern bool operator<=(const ULarge& lcx, const u32 val);
extern bool operator<=(const ULarge& lcx, const ULarge& rcx);