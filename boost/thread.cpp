#include "boost/thread/thread.hpp"
#include <iostream>

class a{
public:
	void print(){
		if(is_change){
			is_change = false;
			std::cout << "now the number a is: " << m_a << std::endl;
		}
	}
public:
	int get_a(){return m_a;}
	void set_a(int a){
		if(m_a != a){
			is_change = true;
			m_a = a;
		}
	}
private:
	int m_a;
	bool is_change;
};

void hello(a* a1, int b){  
	for(int i = 0; i < 4 ;++i){
		a1->print();
		std::cout << "Hello world, I'm a thread! " << b << std::endl;
		++b;
		boost::this_thread::sleep(boost::posix_time::seconds(3));
	}
} 

int main(){
	/*boost::thread th(&hello);
	th.join();*/
	a a1;
	a1.set_a(123);
	boost::thread th1(hello, &a1, 0);
	th1.timed_join(boost::posix_time::seconds(1));
	a1.set_a(312);
	a1.print();

	boost::this_thread::sleep(boost::posix_time::seconds(12));
	return 0; 
}