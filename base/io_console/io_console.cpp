#include <iostream>

using namespace std;

int main(){
	int i;
	cout << "please input i and a string:" << flush;    //只刷新缓冲区，不添加任何字符
	cin >> i;  //cin 与 cout 关联，即 cin 会刷新 cout缓冲区
	cout << "input number:" << i << ends;   //添加一个空字符，刷新缓冲区
	cerr << "test error!"; //cerr 会默认刷新缓冲区，cout 不会
	clog << "test log!";
	cout << endl;    //添加一个换行符，刷新缓冲区
	char str[20];
	cin.getline(str, 20);   //非阻塞式读取
	printf(str);

	auto old_state = cin.rdstate();  //保存状态
	cin.clear();  //去除所有错误状态，并复位
	cin.setstate(old_state);   //还原状态

	cout << unitbuf;    //设置cout像cerr一样，每次输出都清空缓冲区
	cout << nounitbuf;  //回到正常的缓冲方式

	cin.tie(nullptr);  //取消cin与cout的关联，cin不再刷新cout缓冲区
	cin.tie(&cerr);  //关联cin与cerr

	/* 针对宽字符对应 */
	wchar_t c;
	locale::global(locale(""));
	wcout.imbue(locale(""));   //使wcout使用客户端缺省的locale
	wcin.imbue(locale(""));  
	wcout << L"请输入一个宽字符: " << flush;
	wcin >> c;
	wcout << L"输入的宽字符：" << c << endl;
	wcerr << L"测试错误！" << endl;
	wclog << L"测试log！" << endl;
	return 0;
}