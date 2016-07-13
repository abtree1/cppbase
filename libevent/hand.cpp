#include "hand.h"

CHand::CHand(){
}

CHand::~CHand(){
}

void CHand::decode(evhttp_request *req, string& url){
	if(EVHTTP_REQ_GET == req->type){
		parse_get_data(url);
	}else if(EVHTTP_REQ_POST == req->type){
		parse_post_data(req);
	}
}

void CHand::parse_get_data(string url){
	evkeyvalq params;
	evkeyval *param;
	string key,value;
	evhttp_parse_query(url.c_str(), &params);
	for(param = params.tqh_first; param; param = param->next.tqe_next){
		key = string(param->key);
		value = string(param->value);
		mParams.insert(make_pair(key, value));
	}
}

void CHand::parse_post_data(evhttp_request *req){
	char* post_data = (char *)EVBUFFER_DATA(req->input_buffer);
	int bufsize = EVBUFFER_LENGTH(req->input_buffer);
	char *tmp = new char[bufsize + 5];
	ZeroMemory(tmp, bufsize + 5);
	tmp[0] = '/';
	tmp[1] = '?';
	strncpy((char *) &tmp[2], post_data, bufsize);
	string url = tmp;
	parse_get_data(url);
	delete [] tmp;
}