//位运算根据不同的操纵系统可能有不同的结果
//如果考虑代码的移植性 应谨慎使用位操作
#include <iostream>

using namespace std;

typedef unsigned int u32;

#define UBSTR(key, value) printf(#key"._data=%d ", value)
#define FALSE 0x0
#define TRUE 0x1

union UBit{
	struct {
		u32 i1:1;
		u32 i2:1;
		u32 i3:1;
		u32 i4:1;
		u32 i5:1;
		u32 i6:1;
		u32 i7:1;
		u32 i8:1;
		u32 i9:1;
		u32 i10:1;
		u32 i11:1;
		u32 i12:1;
		u32 i13:1;
		u32 i14:1;
		u32 i15:1;
		u32 i16:1;
		u32 i17:1;
		u32 i18:1;
		u32 i19:1;
		u32 i20:1;
		u32 i21:1;
		u32 i22:1;
		u32 i23:1;
		u32 i24:1;
		u32 i25:1;
		u32 i26:1;	
		u32 i27:1;
		u32 i28:1;
		u32 i29:1;
		u32 i30:1;
		u32 i31:1;
		u32 i32:1;
	}_bit;
	u32 _data;
};

void printUBit(UBit* ub){
	cout << "this bit is: " << ub->_bit.i1  << ub->_bit.i2  << ub->_bit.i3  << ub->_bit.i4  << ub->_bit.i5  << ub->_bit.i6  << ub->_bit.i7  << ub->_bit.i8  
		<< ub->_bit.i9  << ub->_bit.i10  << ub->_bit.i11  << ub->_bit.i12  << ub->_bit.i13  << ub->_bit.i14  << ub->_bit.i15  << ub->_bit.i16  
		<< ub->_bit.i17  << ub->_bit.i18  << ub->_bit.i19  << ub->_bit.i20  << ub->_bit.i21  << ub->_bit.i22  << ub->_bit.i23  << ub->_bit.i24  
		<< ub->_bit.i25  << ub->_bit.i26  << ub->_bit.i27  << ub->_bit.i28  << ub->_bit.i29  << ub->_bit.i30  << ub->_bit.i31  << ub->_bit.i32
		<< endl;
}

//设置data的第n位为1
void setTrue(UBit* ub, u32 pos){
	//先检查位不能越界
	if(pos < 0 || pos > 32)
		return;
	u32 i = TRUE << pos;  //16位的1
	ub->_data |= i;
}

//检查data的第n位为1
bool isTrue(UBit* ub, u32 pos){
	//先检查位不能越界
	if(pos < 0 || pos > 32)
		return false;
	u32 i = TRUE << pos;  //16位的1
	UBit k;
	//k._data = (ub->_data & i);
	//printUBit(&k);
	if((ub->_data & i) == i)
		return true;
	return false;
}

//设置data的第n位为0
void setFalse(UBit* ub, u32 pos){
	//先检查位不能越界
	if(pos < 0 || pos > 32)
		return;
	u32 i = TRUE << pos;  //16位的1
	ub->_data ^= i;
}

//获取data的第m到n位的值
void getData(UBit* source, UBit* target, int begin, int end){
	if(!source || !target)
		return;
	if(begin < 0 || end > 32 || begin > end)
		return;
	UBit data;
	data._data = FALSE;
	for(int i = begin; i <= end; ++i){
		setTrue(&data, i);
	}
	printUBit(&data);
	target->_data = source->_data & data._data;
}

//复制data的第m到n位的值
void copyData(UBit* source, UBit* target, int tbegin, int sbegin, int send){
	if(!source || !target)
		return;
	if(sbegin < 0 || send > 32 || sbegin > send)
		return;
	if(tbegin < 0 || tbegin + send - sbegin > 32)
		return;
	//先清理target相应位置的数据 再拷贝目标位置的数据
	while(sbegin <= send){
		if(isTrue(source, sbegin)){
			setTrue(target, tbegin);
		}else{
			setFalse(target, tbegin);
		}
		++tbegin;
		++sbegin;
	}
}

int main(){
//基本位移操作
	UBit i,j;
	i._data = 16;
	UBSTR(i, i._data);
	printUBit(&i);
	j._data = i._data << 2; // i << 2 + 1 等同于 i << (2 + 1)
	UBSTR(j, j._data);
	printUBit(&j);
	j._data = i._data >> 2;
	UBSTR(j, j._data);
	printUBit(&j);
//位运算 运算符优先级从高到低 ~(非) > &(于) > ^(异或) > |(或)
	UBit k;
	k._data = ~i._data;  //按位取返
	UBSTR(k, k._data);
	printUBit(&k);
	k._data = i._data & j._data;  //按位取于
	UBSTR(k, k._data);
	printUBit(&k);
	k._data = i._data | j._data;  //按位取或
	UBSTR(k, k._data);
	printUBit(&k);
	k._data = i._data ^ k._data;  //按位异或
	UBSTR(k, k._data);
	printUBit(&k);
//一些惯用操作
	setTrue(&i, 5);
	UBSTR(i, i._data);
	printUBit(&i);

	cout << "pos 5 is " << isTrue(&i, 5) << " and pos 6 is " << isTrue(&i, 6) << endl;
	
	setFalse(&i, 5);
	UBSTR(i, i._data);
	printUBit(&i);
	
	setTrue(&i, 5);
	setTrue(&i, 6);
	k._data = FALSE;
	getData(&i, &k, 4, 6);
	cout << "get data:";
	printUBit(&k);
	
	copyData(&i, &k, 10, 4, 6);
	cout << "copy data: ";
	printUBit(&k);

	return 0;
}
