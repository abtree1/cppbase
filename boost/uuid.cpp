#include"boost\uuid\uuid.hpp"
#include"boost\uuid\uuid_generators.hpp"
#include"boost\uuid\uuid_io.hpp"
#include"boost\lexical_cast.hpp"
#include<iostream>
#include<vector>
#include<string>

int main(){ 
	boost::uuids::random_generator rgen;
	boost::uuids::uuid _uuid(rgen());
	std::cout<<_uuid<<std::endl;
	std::string str = boost::lexical_cast<std::string>(_uuid);
	std::cout<<str.c_str()<<std::endl;
	std::vector<unsigned char> v(16, 7);
	//ʹ�ñ�׼�����㷨
	std::copy(v.begin(), v.end(), _uuid.begin());
	std::cout<<_uuid<<std::endl;
	std::fill_n(_uuid.data + 10, 6, 8); //��׼�㷨fill_nֱ�Ӳ�������
	std::cout<<_uuid<<std::endl;
	return 0;
}