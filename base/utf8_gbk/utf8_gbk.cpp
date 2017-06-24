//该函数在windows下运行
//如果在其他操作系统 需要修改 GBK_LOCALE_NAME 的值
#include <iostream>
#include <cvt/wstring>
#include <codecvt>
#include <string>
#include <locale>

using namespace std;

const char* GBK_LOCALE_NAME = ".936";  //gbk

int main(){
	string utf8_str{u8"你好啊！"};

	//首先 将原有字符转换为宽字符
	wstring_convert<codecvt_utf8<wchar_t>> cv1;
	wstring tmp_wstr = cv1.from_bytes(utf8_str);
	//检查转换是否被支持
	locale lc(GBK_LOCALE_NAME);
	bool can_cvt = has_facet<codecvt_byname<wchar_t, char, mbstate_t>>(lc);
	if (!can_cvt)
		cout << "Do not support !!" << endl;

	//在将宽字符转换为gbk字符
	wstring_convert<codecvt_byname<wchar_t, char, mbstate_t>> cv2(new codecvt_byname<wchar_t, char, mbstate_t>(GBK_LOCALE_NAME));
	string gbk_str = cv2.to_bytes(tmp_wstr);

	return 0;
}