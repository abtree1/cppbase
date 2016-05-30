#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

bool isoperator(char op)  
{  
	switch(op)  
	{  
	case '+':  
	case '-':  
	case '*':  
	case '/':  
		return 1;  
	default :   
		return 0;  
	}  
} 

int priority(char op)  
{  
	switch(op)  
	{  
	case '#':  
		return -1;  
	case '(':  
		return 0;  
	case '+':  
	case '-':  
		return 1;  
	case '*':  
	case '/':  
		return 2;  
	default :  
		return -1;  
	}  
}

void postfix(string buf,vector<char> &vec){
	stack<char> sta;
	for (int i = 0;i<buf.length();i++)
	{
		if((buf[i]>='a' && buf[i] <='z')) // 遇见字符直接写入后缀表达式
		{
			vec.push_back(buf[i]);
		}  
		else if (buf[i]=='('){   // 遇到“（”不用比较直接入栈  
			sta.push(buf[i]);
		}
		else if(buf[i] ==')')  // 遇到右括号将其对应左括号后的操作符（操作符栈中的）全部写入后缀表达式  
		{  
			while(sta.top() != '(')  
			{  
				vec.push_back(sta.top());
				sta.pop();
			}  
			sta.pop(); //此时j正好在“（”位置的前一位
		}  
		else if (isoperator(buf[i]))  
		{  
			while(!sta.empty() && priority(buf[i]) <= priority(sta.top()))   
			{  
				// 当前的操作符小于等于栈顶操作符的优先级时，将栈顶操作符写入到后缀表达式，重复此过程  
				vec.push_back(sta.top());
				sta.pop();
			}  

			sta.push(buf[i]);// 当前操作符优先级大于栈顶操作符的优先级，将该操作符入栈 
		}  
	}

	while(!sta.empty()){
		vec.push_back(sta.top());
		sta.pop();
	}
}

int postfix_value(vector<char> &vec){
	stack<int> sta;
	int x1,x2;

	vector<char>::iterator it = vec.begin();
	while (it!= vec.end())
	{
		if(!isoperator(*it)){
			sta.push(*it - 'a' + 1);
		}else if((*it) == '+'){
			x2 = sta.top();
			sta.pop();
			x1 = sta.top();
			sta.pop();
			sta.push(x1+x2);
		}else if((*it) == '-'){
			x2 = sta.top();
			sta.pop();
			x1 = sta.top();
			sta.pop();
			sta.push(x1-x2);
		}else if((*it) == '*'){
			x2 = sta.top();
			sta.pop();
			x1 = sta.top();
			sta.pop();
			sta.push(x1*x2);
		}else if((*it) == '/'){
			x2 = sta.top();
			sta.pop();
			x1 = sta.top();
			sta.pop();
			sta.push(x1/x2);
		}
		it++;
	}
	return sta.top();
}

//如果需要带入参数，需要在求值时替换abcd的值
int main(){
	string before = "d*(a+b*c)*d+(a*c+d)";//"(a+b*c)*d+a";
	vector<char> after;
	//中缀表达式转后缀表达式
	postfix(before,after);
	//cout << after << endl;
	//后缀表达式求值
	int ret = postfix_value(after);
	cout << ret << endl;
	return 0;
}