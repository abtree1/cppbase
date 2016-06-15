#include<iostream>
#include"boost\timer.hpp"
#include"boost\progress.hpp"
#include<vector>
#include<fstream>
// boost::timer��, �������ܲ��Ե���Ҫ��ʱ������   
// boost::timer���ʺϸ߾��ȵ�ʱ��������� ���ľ��������ڲ���ϵͳ�������������������ƽ̨��   
// boost::timerҲ���ʺϴ���ʱ��εĲ��������ṩ�������ֻ�м��ٸ�Сʱ�������Ҫ���졢����������Ϊʱ��ĵ�λ����ʹ��timer�� Ӧ��ʹ�� date_time�⡣  
void test_timer()  
{  
    // ����һ����ʱ�����󣬲���ʼ��ʱ!  
    boost::timer t;  
  
    long long sum = 0;  
    for (int i = 0; i < 1000000 ; i++)  
        sum = sum + i;  
  
    // ����ʱ���, �����Զ��󴴽��������ŵ�ʱ�䡣  
    double dl = t.elapsed();  
    std::cout << "now time elapsed:" << dl << std::endl;  
  
    //�ɶ��������ʱ�䣬����Ϊ��λ      
    std::cout << "max timespan:" << t.elapsed_max() /3600 << "h" << std::endl;  
    //�ɶ�������Сʱ�䣬����Ϊ��λ  
    std::cout << "min timespan:" << t.elapsed_min() << "s" << std::endl;  
  
    // ����һ��restart()��ʼ���¼�ʱ  
    t.restart();  
}  
  
// boost::progress_timerҲ��һ����ʱ�������̳���timer��  
// ����������ʱ�Զ����ʱ�䣬ʡȥ��boost::timer�ֶ�����elapsed()�Ĺ�������һ�������Զ���ʱ�൱�����С���ߡ�  
void test_progress_timer()  
{  
    boost::progress_timer pt;  
  
    long long sum = 0;  
    for (int i = 0; i < 10000000 ; i++)  
        sum = sum + i;  
  
    pt.elapsed();  
  
    // ����һ�ַ�������Ҫ��el  
    {  
        boost::progress_timer pt;  
        // do_something();  
    }   // pt����ʱ�Զ��������ʱ��  
}  
  
void test_progress_display()  
{  
    std::vector<std::string> v(1000000, "abcdefg");  
    std::ofstream fs("d:\\test.txt");  
  
    // ����һ��progress_display ���󣬻�����v�Ĵ�С  
    boost::progress_display pd(v.size());  
  
    // ��ʼѡ�����������������ַ���  
    std::vector<std::string>::iterator pos;  
    for (pos = v.begin(); pos != v.end(); ++pos)  
    {  
        fs << *pos << std::endl;  
        ++pd; // ���½�����ʾ  
    }  
}  
  
// ���ȱ��ڴ�ӡ�����г���Ĵ���  
void test_progress_display_restart()  
{  
    std::vector<std::string> v(100 , "abcd");  
    v[10] = "";  
    v[23] = "";  
    std::ofstream fs("d:\\test.txt");  
    boost::progress_display pd(v.size());  
    std::vector<std::string>::iterator pos;  
    for (pos = v.begin(); pos != v.end(); ++pos)  
    {  
        fs << *pos << std::endl;  
        ++pd;  
        if (pos->empty())  
        {  
            std::cout << std::endl;  
            std::cout << "Error: null string # " << (pos - v.begin())<< std::endl;  
            pd.restart(v.size());  
            pd += (pos - v.begin() + 1);  
        }  
    }  
}  