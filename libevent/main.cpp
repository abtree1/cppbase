#include "hand.h"

void handler(evhttp_request *req, void *arg){
	CHand *hand = (CHand*)arg;
	if(!hand) return;

	evbuffer *buf = evbuffer_new();
	if(!buf) return;

	string url = evhttp_request_get_uri(req);
	//解析参数
	hand->decode(req, url);
	//设置返回
	string result = "success";
	evbuffer_add_printf(buf, result.c_str());
	evhttp_send_reply(req, HTTP_OK, "OK", buf);
	evbuffer_free(buf);
}

bool init_win_socket(){
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2,2), &wsaData);
	if(ret != 0){
		return false;
	}
	return true;
}

int main(){
	//先创建 win socket
	if(!init_win_socket()) return 0; 

	CHand *hand = new CHand();

	//创建lib event 监听
	hand->base =  event_base_new();
	if(!hand->base) return 0;

	hand->http_server = evhttp_new(hand->base);
	if(!hand->http_server) return 0;

	short http_port = 8666;
	char http_addr[] = "0.0.0.0";
	int ret = evhttp_bind_socket(hand->http_server, http_addr, http_port);
	if(ret != 0) return 0;

	evhttp_set_gencb(hand->http_server, handler, hand);
	event_base_dispatch(hand->base);
	evhttp_free(hand->http_server);
	delete hand;
	return 0;
}