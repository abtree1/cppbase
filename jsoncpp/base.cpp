#include <iostream>
#include <string>
#include "json\json.h"

#pragma comment(lib, "E:/Github/jsoncpp/makefiles/msvc2010/Debug/lib_json.lib");

using namespace std;

int main(){
	
	//string jsonstr = "{\"awardlist\":[{\"roleId\":\"2192934\",\"serverId\":\"1011\",\"zoneId\":\"100\",\"roleName\":\"º‚º‚Õ∑\",\"serverName\":\"«Ì÷¶”≥—©\",\"zoneName\":\"11∑˛-«Ì÷¶”≥—©\",\"partyName\":\"\",\"channel\":\"ios_xiaomiApple\",\"account\":\"ios_xiaomiApple__5508180\",\"questionnaireId\":\"f7d9c7c7-8c1a-47c2-8c4a-91fa80191a07\",\"giftInfo\":\"20016\",\"groupId\":\"1011\",\"time\":1486548505708}]}";
	string jsonstr = "{ \
	\"activity_type\": 6, \
	\"model\": { \
	\"blackboard\": \"1\", \
        \"index_icon\": \"1\", \
        \"ui_bottom\": \"1\", \
        \"is_daily\": 0, \
        \"activity_open_condition_or_and\": 0, \
        \"handle_type\": 0, \
        \"activity_open_condition\": { \
            \"open_server_time_greater\": 0 \
        } \
    }, \
    \"time\": { \
        \"time_type\": 1, \
        \"open_datetime\": \"2017-03-16 01:00:00\", \
        \"end_datetime\": \"2017-03-18 01:00:00\", \
        \"open_daytime\": \"2,00:00:00\", \
        \"end_daytime\": \"3,00:00:00\" \
    }, \
    \"activity_content\": { \
    	\"activity_desc1\":\"\", \
    	\"activity_desc2\":\"\", \
    	\"hero_id\":23, \
    	\"limit_power\":34560, \
    	\"clearing_time\":\"2017-03-18 01:00:00\", \
    	\"award\":[ \
    		{ \
    			\"rank\":1, \
    			\"goods\":[\"1*0*1000\",\"2*0*100\",\"6*23_1*1\",\"0*0*0\"] \
    		}, \
    		{ \
    			\"rank\":2, \
    			\"goods\":[\"1*0*900\",\"2*0*90\",\"6*23_1*1\",\"0*0*0\"] \
    		}, \
    		{ \
    			\"rank\":3, \
    			\"goods\":[\"1*0*800\",\"2*0*80\",\"6*23_1*1\",\"0*0*0\"] \
    		}, \
    		{ \
    			\"rank\":4, \
    			\"goods\":[\"1*0*700\",\"2*0*70\",\"6*23_1*1\",\"0*0*0\"] \
    		}, \
    		{ \
    			\"rank\":5, \
    			\"goods\":[\"1*0*600\",\"2*0*60\",\"6*23_1*1\",\"0*0*0\"] \
    		}, \
    		{ \
    			\"rank\":6, \
    			\"goods\":[\"1*0*500\",\"2*0*50\",\"6*23_1*1\",\"0*0*0\"] \
    		}, \
    		{ \
    			\"rank\":7, \
    			\"goods\":[\"1*0*400\",\"2*0*40\",\"6*23_1*1\",\"0*0*0\"] \
    		}, \
    		{ \
    			\"rank\":8, \
    			\"goods\":[\"1*0*300\",\"2*0*30\",\"6*23_1*1\",\"0*0*0\"] \
    		}, \
    		{ \
    			\"rank\":9, \
    			\"goods\":[\"1*0*200\",\"2*0*20\",\"6*23_1*1\",\"0*0*0\"] \
    		}, \
    		{ \
    			\"rank\":10, \
    			\"goods\":[\"1*0*100\",\"2*0*10\",\"6*23_1*1\",\"0*0*0\"] \
    		} \
    	] \
    } \
}";
	{
		using namespace Json;
		Reader reader;
		Value root;
		Value data;
		reader.parse(jsonstr, root);
		if(root.type() != objectValue){
			cout << "parse error!";
			return 0;
		}
		root = root["activity_content"];
		cout << "activity_desc1: " << root["activity_desc1"].asString() << endl;
		cout << "activity_desc2: " << root["activity_desc2"].asString() << endl;
		cout << "heroid: " << root["hero_id"].asInt() << endl;
		cout << "limit_power: " << root["limit_power"].asInt() << endl;
		cout << "clearing_time: " << root["clearing_time"].asString() << endl;
		int size = root["award"].size();
		int gsize;
		int type;
		string name;
		int count;
		for(int i = 0; i < size; ++i){
			data = root["award"][i];
			cout << "rank: " << data["rank"].asInt() << endl;
			gsize = data["goods"].size();
			cout << "goods: ";
			for(int j = 0; j < gsize; ++j){
				string str = data["goods"][j].asString(); 
				sscanf_s(str.c_str(), "%d*%s*%d", &type, &name,&count);
				cout << type << " " << name.c_str() << " " << count << " ";
			}
			cout << endl;
		}
		//root = root["awardlist"];
		//cout << root.isArray() << " " << root.size() << endl;
		//Value data = root[0];
		//cout << data["roleId"].asString() << ":" << data["serverId"].asString() << endl; 
		/*for(auto it = root.begin(); it != root.end();++it){
			cout << it.key().asString().c_str() << " " << it->toStyledString() << endl;
		}*///root[it.key().asString()].toStyledString()
		//cout << "************************************************";
		/*if(!root["errorno"].isInt()){
			cout << "errorno error" << endl;
			return 0;
		}
		cout << "errorno=" << root["errorno"].asInt() << endl;
		cout << "errormsg=" << root["errormsg"].asString().c_str() << endl;
		if(root["errormsg"].isNull()){
			cout << "msg is null!" << endl;
		}
		if(root["errorno"].isDouble()){
			cout << to_string((int)root["errorno"].asDouble()) << endl;
		}
		if(root["asdasdasd"].asInt() == 0){
			cout << "not key cannot equ 0" << endl;
		}
		if(root["asdasdasd"].isNull()){
			cout << "not key cannot equ 0" << endl;
		}
		root = root["data"];
		cout << "guid=" << root["guid"].asString().c_str() << endl;
		cout << "username=" << root["username"].asString().c_str() << endl;*/
	}
	return 0;
}