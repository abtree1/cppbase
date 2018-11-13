#include "ULarge.h"

ULarge::ULarge(u32 val):_rem(val) {

}

ULarge::ULarge(const ULarge& other)
	: _rem(other._rem)
	, _pow(other._pow) {

}

ULarge::ULarge(u32 pow, u32 rem)
	: _pow(pow)
	, _rem(rem) {

}

ULarge::ULarge(string val) {
	const char* p = val.c_str();
	const char* end = p + val.size();
	const char* pva = p, *pvi = nullptr;

	for (; p != end; ++p) {
		if (*p == '^') {
			pvi = p + 1;
			break;
		}
	}
	if (pva + 1 != pvi)   //如果不传实数部分 为0
		_pow = atoi(pva);  //如果不传虚数部分 为0
	if (pvi != nullptr)
		_rem = atoi(pvi);
}

ULarge &ULarge::operator =(const ULarge& other) {
	this->_pow = other._pow;
	this->_rem = other._rem;
	return *this;
}

ULarge &ULarge::operator +=(const u32 val) {
	u32 pow = val / ULarge::_max;
	u32 rem = val % ULarge::_max;
	_pow += pow;
	u32 a = ULarge::_max - _rem;
	if (rem >= a) {
		_rem += rem - a;
		_pow += 1;
	}
	else {
		_rem += rem;
	}
	return *this;
}

ULarge &ULarge::operator +=(const ULarge &other) {
	_pow += other._pow;
	u32 a = ULarge::_max - _rem;
	if (other._rem >= a) {
		_pow += 1;
		_rem += other._rem - a;
	}
	else {
		_rem += other._rem;
	}
	return *this;
}

ULarge &ULarge::operator -=(const u32 val) {
	u32 pow = val / ULarge::_max;
	u32 rem = val % ULarge::_max;
	if (pow > _pow) {
		_pow = 0;
		_rem = 0;
		return *this;  //不够减的 就归0
	}
	_pow -= pow;
	if (rem > _rem) {
		if (_pow > 0) {
			--pow;
			rem -= _rem;
			_rem = ULarge::_max - rem;
		}
		else {
			_rem = 0; //不够减就归0
		}
	}
	else {
		_rem -= rem;
	}
	return *this;
}

ULarge &ULarge::operator -=(const ULarge &other) {
	if (other._pow > _pow) {
		_pow = 0;
		_rem = 0;
		return *this; //不够减的 就归0
	}
	_pow -= other._pow;
	if (other._rem > _rem) {
		if (_pow > 0) {
			--_pow;
			u32 val = other._rem - _rem;
			_rem = ULarge::_max - val;
		}
		else {
			_rem = 0; //不够减的 就归0
		}
	}
	else {
		_rem -= other._rem;
	}
	return *this;
}

u32 ULarge::operator [](bool pow) {
	if (pow)
		return _pow;
	return _rem;
}

//文本运算符只能是全局的
ULarge operator ""_un(const char* col, size_t n) { //将形如 "123^32"_UL 的字符串隐式转换为ULarge类型对象
	const char* p = col;
	const char* end = col + n;
	const char* pva = col, *pvi = nullptr;

	for (; p != end; ++p) {
		if (*p == '^') {
			pvi = p + 1;
			break;
		}
	}

	int iva = 0;
	int ivi = 0;
	if (pva + 1 != pvi)   //如果不传实数部分 为0
		iva = atoi(pva);  //如果不传虚数部分 为0
	if (pvi != nullptr)
		ivi = atoi(pvi);

	return ULarge(iva, ivi);
}

ULarge operator+(const ULarge& lcx, const u32 val) {
	ULarge tmp(lcx);
	tmp += val;
	return tmp;
}

ULarge operator+(const ULarge& lcx, const ULarge& rcx) {
	ULarge tmp(lcx);
	tmp += rcx;
	return tmp;
}

ULarge operator-(const ULarge& lcx, const u32 val) {
	ULarge tmp(lcx);
	tmp -= val;
	return tmp;
}

ULarge operator-(const ULarge& lcx, const ULarge& rcx) {
	ULarge tmp(lcx);
	tmp -= rcx;
	return tmp;
}

double operator/(const ULarge& lcx, const u32 val) {
	ULarge tmp(val);
	return lcx / tmp;
}

double operator/(const ULarge& lcx, const ULarge& rcx) {
	if (rcx == 0)
		return 0;	//如果分母为0 直接返回 
	return (lcx._pow + lcx._rem * 1.0 / ULarge::_max) / (rcx._pow + rcx._rem * 1.0 / ULarge::_max);
}

ULarge operator*(const ULarge& lcx, const u32 val) {
	//乘法不能运算太大的值
	lcx._pow = lcx._pow * val + lcx._rem * val / ULarge::_max;
	lcx._rem = lcx._rem * val % ULarge::_max;
}

bool operator==(const ULarge& lcx, const u32 val) {
	ULarge tmp(val);
	if (tmp == lcx)
		return true;
	return false;
}

extern bool operator==(const ULarge& lcx, const ULarge& rcx) {
	if (lcx._pow == rcx._rem &&
		lcx._rem == rcx._rem)
		return true;
	return false;
}

extern bool operator!=(const ULarge& lcx, const u32 val) {
	if (lcx == val)
		return false;
	return true;
}
extern bool operator!=(const ULarge& lcx, const ULarge& rcx) {
	if (lcx == rcx)
		return false;
	return true;
}
bool operator>(const ULarge& lcx, const u32 val) {
	ULarge tmp(val);
	return lcx > tmp;
}
bool operator>(const ULarge& lcx, const ULarge& rcx) {
	if (lcx._pow > rcx._pow)
		return true;
	else if (lcx._pow < rcx._pow)
		return false;
	else
		return lcx._rem > rcx._rem;
}
bool operator>=(const ULarge& lcx, const u32 val) {
	if (lcx > val)
		return true;
	if (lcx == val)
		return true;
	return false;
}
bool operator>=(const ULarge& lcx, const ULarge& rcx) {
	if (lcx > rcx)
		return true;
	if (lcx == rcx)
		return true;
	return false;
}
bool operator<(const ULarge& lcx, const u32 val) {
	if (lcx >= val)
		return false;
	return true;
}
bool operator<(const ULarge& lcx, const ULarge& rcx) {
	if (lcx >= rcx)
		return false;
	return true;
}
bool operator<=(const ULarge& lcx, const u32 val) {
	if (lcx > val)
		return false;
	return true;
}
bool operator<=(const ULarge& lcx, const ULarge& rcx) {
	if (lcx > rcx)
		return false;
	return true;
}