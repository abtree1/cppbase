#include<iostream>
#include"boost\timer.hpp"
#include"boost\progress.hpp"
#include<vector>
#include<fstream>
// boost::timer库, 用于性能测试等需要计时的任务。   
// boost::timer不适合高精度的时间测量任务。 它的精度依赖于操作系统或编译器，难以做到跨平台。   
// boost::timer也不适合大跨度时间段的测量，可提供的最大跨度只有几百个小时，如果需要以天、月甚至年作为时间的单位则不能使用timer。 应该使用 date_time库。  
void test_timer()  
{  
    // 声明一个计时器对象，并开始计时!  
    boost::timer t;  
  
    long long sum = 0;  
    for (int i = 0; i < 1000000 ; i++)  
        sum = sum + i;  
  
    // 计算时间差, 测量自对象创建后所流逝的时间。  
    double dl = t.elapsed();  
    std::cout << "now time elapsed:" << dl << std::endl;  
  
    //可度量的最大时间，以秒为单位      
    std::cout << "max timespan:" << t.elapsed_max() /3600 << "h" << std::endl;  
    //可度量的最小时间，以秒为单位  
    std::cout << "min timespan:" << t.elapsed_min() << "s" << std::endl;  
  
    // 还有一个restart()开始重新计时  
    t.restart();  
}  
  
// boost::progress_timer也是一个计时器，它继承自timer，  
// 它会在析构时自动输出时间，省去了boost::timer手动调用elapsed()的工作，是一个用于自动计时相当方便的小工具。  
void test_progress_timer()  
{  
    boost::progress_timer pt;  
  
    long long sum = 0;  
    for (int i = 0; i < 10000000 ; i++)  
        sum = sum + i;  
  
    pt.elapsed();  
  
    // 另外一种方法，不要用el  
    {  
        boost::progress_timer pt;  
        // do_something();  
    }   // pt析构时自动输出流逝时间  
}  
  
void test_progress_display()  
{  
    std::vector<std::string> v(1000000, "abcdefg");  
    std::ofstream fs("d:\\test.txt");  
  
    // 声明一个progress_display 对象，基数是v的大小  
    boost::progress_display pd(v.size());  
  
    // 开始选代遍历向量，处理字符串  
    std::vector<std::string>::iterator pos;  
    for (pos = v.begin(); pos != v.end(); ++pos)  
    {  
        fs << *pos << std::endl;  
        ++pd; // 更新进度显示  
    }  
}  
  
// 进度表在打印过程中出错的处理  
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