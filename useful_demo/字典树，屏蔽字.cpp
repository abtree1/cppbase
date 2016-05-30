#include<iostream>
#include<string>
#include<map>
#include<list>
using namespace std;

typedef unsigned short USHORT; 
typedef map<char, void*> MapTree;
typedef const char* CStr;

void degue_str(MapTree *father, USHORT pos, CStr source){
	auto vchild = father->find(source[pos]);
	MapTree *child;
	if(vchild != father->end()){
		child = (MapTree*)vchild->second;
	}else{
		child = new MapTree();
		father->insert(make_pair(source[pos], child));
	}
	++pos;
	if (source[pos] != '\0'){
		degue_str(child, pos, source);
	}else{
		if(child->find('\0') == child->end()){
			MapTree *end = new MapTree();
			child->insert(make_pair('\0', nullptr));
		}
	}
}

USHORT match_map_tree(MapTree* father, USHORT pos, CStr source){
	auto vchild = father->find(source[pos]);
	if(vchild != father->end()){
		if(source[pos] == '\0'){
			return pos;
		}else{
			MapTree* child =(MapTree*)vchild->second;
			if(child->find('\0') != child->end())
				return pos;
			else
				return match_map_tree(child, ++pos, source);
		}
	}
	return 0;
}

void clear_map_tree(MapTree* father){
	if(father == nullptr) return;
	for (auto it = father->begin(); it != father->end(); ++it){
		clear_map_tree((MapTree *)it->second);
	}
	delete father;
}

int main(){
	list<string> lists;
	lists.push_back("张三");
	lists.push_back("张四");
	lists.push_back("李四");
	lists.push_back("李五");

	//创建字典树
	MapTree *m_DicHead;
	m_DicHead = new MapTree();
	for (string str : lists){
		USHORT pos = 0;
		CStr chars = str.c_str();
		degue_str(m_DicHead, pos, chars);
	}

	//查询字典树
	string test = "ask觉得哈数据库李五啊uishduh";
	CStr testc = test.c_str();
	USHORT b = 0;
	for (int i = 0; i < strlen(testc); ++i){
		USHORT j = i;
		b = match_map_tree(m_DicHead, j, testc);
		if(b > 0){
			cout << "matched: " << testc << " in pos: " << i << " to pos: " << b << endl; 
			for(USHORT k = i; k <= b; ++k){
				test[k] = '*';
			}
			cout << test.c_str() << endl;
			break;
		}
	}
	if(!b)
		cout << "failed to match: " << testc << endl;
	
	//清除操作 释放内存
	for (auto it = m_DicHead->begin(); it != m_DicHead->end(); ++it){
		clear_map_tree((MapTree *)it->second);
	}
	delete m_DicHead;
	return 0;
}