#include "boost\lexical_cast.hpp"
#include <string>

int convert_strings_part(const std::string& s, std::size_t pos, std::size_t n)
{
    return boost::lexical_cast<int>(s.data() + pos, n);
}

int main(){
	std::string str = "123";
	int a = boost::lexical_cast<int>(str);
	double b = boost::lexical_cast<double>(str);
	printf("to integer is: %d and to double is: %.2f \n", a, b);

	std::array<char, 4> buff = boost::lexical_cast<std::array<char, 4>>(str);
	char *cstr = buff.data();
	printf("to buff: %c, to c string %c \n", buff[0], cstr[2]);
	
	try {  
		int c = boost::lexical_cast<int>("wrong number");  
	}catch(boost::bad_lexical_cast & e){
		printf("%s \n", e.what());       
	}

	a = convert_strings_part("aaa321bbb", 3, 3);
	printf("sub integer is: %d \n", a);
	return 0;
}