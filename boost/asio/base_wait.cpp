#include"boost\asio.hpp"
#include"boost\date_time\posix_time\posix_time.hpp"
#include"boost\bind.hpp"
#include<iostream>

void base_wait(){
	boost::asio::io_service io;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
	t.wait();
	std::cout << "wait 5 seconds" << std::endl;
}

void print(boost::system::error_code& e){
	std::cout << "Hello World" << std::endl;
}

void print1(const boost::system::error_code& /*e*/,boost::asio::deadline_timer* t, int* count)
{
  if (*count < 5)
  {
    std::cout << *count << std::endl;
    ++(*count);

    t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
    t->async_wait(boost::bind(print,boost::asio::placeholders::error, t, count));
  }
}

void async_base_wait(){
	boost::asio::io_service io;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
	t.async_wait(&print);
	io.run();
}

void bind_base_wait(){
	boost::asio::io_service io;
	int count = 0;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
	t.async_wait(boost::bind(print1,boost::asio::placeholders::error, &t, &count));
	io.run();
	std::cout << "Final count is " << count << std::endl;
}

class printer
{
public:
  printer(boost::asio::io_service& io)
    : timer_(io, boost::posix_time::seconds(1)),
      count_(0)
  {
    timer_.async_wait(boost::bind(&printer::print, this));
  }

  ~printer()
  {
    std::cout << "Final count is " << count_ << std::endl;
  }

  void print()
  {
    if (count_ < 5)
    {
      std::cout << count_ << std::endl;
      ++count_;

      timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
      timer_.async_wait(boost::bind(&printer::print, this));
    }
  }

private:
  boost::asio::deadline_timer timer_;
  int count_;
};

void class_base_wait(){
	boost::asio::io_service io;
	printer p(io);
	io.run();
}

int main(){
	//base_wait();
	//async_base_wait();
	//bind_base_wait();
	class_base_wait();
	std::cout << "main" << std::endl;
	return 0;
}