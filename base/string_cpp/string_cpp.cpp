#include<iostream>
#include<string>
#include<cctype>

using namespace std;

//utf8 string
string utf8str = u8"I am UTF8";
u16string u16str = u"I am UTF16 string";
u32string u32str = U"I am UTF32 string";

//原生字符串（不会解析转义字符）
string rstr = R"("I" "AM" "A" "STRING")";  //这是一个字符串
string utf8str = u8R"(I am UTF8)";
u16string u16str = uR"(I am UTF16 string)";
u32string u32str = UR"(I am UTF32 string)";

void base_str();
void create_str();
void find_str();
void deal_str();
void trans_str();

int main(){
	base_str();
	create_str();
	find_str();
	deal_str();
	trans_str();
	return 0;
}

void base_str(){
	string s1;
	string s2 = "value";
	string s3(s2);
	string s4 = s2;
	string s5(10, 'c');
	cout << s5 << endl;
	cout << "input string: " << endl;
	cin >> s1;
	if (!s1.empty()){
		cout << s1 << endl;
	}
	cout << "input string > 20: " << endl;
	getline(cin, s2);
	if (s2.size() < 10){
		cout << s2 << endl;
	}
	if (s3 == s4){
		cout << s3 << endl;
	}
	// "\n" 不是 string 类型常量
	s4 += s3 + "\n";
	cout << s4 << endl;

	//遍历string
	string str("as d123\ts\n1AS0Cs;asd\x2");
	auto size = str.size();
	cout << "size: " << size << endl;
	for (auto c : str){
		string tmp = "";
		//定义在 cctype 的字符处理函数
		if (isalnum(c)){   //字母或数字
			tmp += " a num or letter; ";
		}
		if (isalpha(c)){   //字母
			tmp += " a letter; ";
		}
		if (iscntrl(c)){   //控制符
			tmp += " a controll; ";
		}
		if (isdigit(c)){    //数字
			tmp += " a num; ";
		}
		if (isgraph(c)){    //除空格的可打印字符
			tmp += " a char not space; ";
		}
		if (islower(c)){     //小写字母
			tmp += " a lower; " + toupper(c);  //转换为大写字母
		}
		if (isprint(c)){     //可打印字符
			tmp += " a char; ";
		}
		if (ispunct(c)){      //标点符号
			tmp += " a punct; ";
		}
		if (isspace(c)){       //空白时 空格 回车 制表符 换行符 进制符等
			tmp += " a space; ";
		}
		if (isupper(c)){       //大写字母
			tmp += " a upper; " + tolower(c);
		}
		if (isxdigit(c)){      //16进制
			tmp += " a \x000; ";
		}
		cout << tmp << endl;
	}

	//改变字符串的值
	str = "hello world!";
	for (auto &c : str){
		c = toupper(c);
	}
	str[2] = tolower(str[2]);   //改变字符串中下标为2的字符的值
	cout << "toupper str: " << str << endl;
}

void create_str(){
	const char *cp = "hello world!";
	char nonull[] = { 'H', 'i' };
	string s1(cp); 
	string s2(nonull, 2);  //末尾会加上结束符
	string s3(cp + 6, 5);
	string s4(s1, 6, 5);
	string s6(s1, 6);
}

void find_str(){
	string s("aaaabbbbccccdddd");
	auto pos1 = s.find("bbbb");
	auto pos2 = s.rfind("cccc");
	auto pos3 = s.find_first_of("cccc");     //返回开始位置，即8
	auto pos4 = s.find_first_not_of("dddd");  //返回结束位置的下一个位置，为结束符位置
	auto pos5 = s.find_last_of("bbbb");
	auto pos6 = s.find_last_not_of("aaaa");
}

void deal_str(){
	string s("hello world!");
	s.substr(6, 5);  //截取从第六位开始，五个元素
	s.insert(s.size(), 5, 'i'); //末尾插入五个！
	s.erase(s.size() - 5, 5);
	s.assign("halllllllo", 7);
	s.append(" worrrrrld!");
	s.replace(4, 3, "ooo");  //从第四位开始，删除3个，插入后面的字符串
}

void trans_str(){
	int i = 10;
	string s = to_string(i); //to_wstring() 
	s = "12_12.3";
	i = stoi(s, 0, 2);
	s = "12.3";
	auto d = stod(s);
}

void split_str(){
	string str = "12;32;123;234";
	char *token = strtok((char *)str.c_str(), ";");
    while(token) {
		printf("%d \t", atoi(token));
        token = strtok(NULL, ";");
    }
	printf("\n");
}