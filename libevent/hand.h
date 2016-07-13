#include <iostream>
#include <string>
#include <map>

#include "libevent\event2\http_struct.h"
#include "libevent\event2\buffer_compat.h"
#include "libevent\event2\http.h"
#include "libevent\event2\event.h"
#include "libevent\event2\buffer.h"
#include "libevent\event2\keyvalq_struct.h"

using namespace std;

class CHand
{
public:
	CHand();
	~CHand();
public:
	void decode(evhttp_request *req, string& url);
private:
	void parse_get_data(string url);
	void parse_post_data(evhttp_request *req);
public:
	event_base *base;
	evhttp* http_server;
private:
	map<string, string> mParams;
};