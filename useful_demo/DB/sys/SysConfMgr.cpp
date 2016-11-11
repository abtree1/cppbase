#include "SysConfMgr.h"

SysConfMgr::SysConfMgr()
{
}

SysConfMgr::~SysConfMgr()
{
}

bool SysConfMgr::createFromPeiZhi(std::string filename){
	std::string peizhi = "";
	if(!CReadConf::GetInstance()->readAllData_s(filename, peizhi)){
		return false;
	}
	//xml配置解析
	mStructs.push_back("#pragma once \n");
	mStructs.push_back("#include <string> \n");
	try{
		xml_document<> doc;
		doc.parse<0>((char *)peizhi.c_str());
		auto node = doc.first_node();
		while(node){
			if(strcmp(node->name(), "DB") == 0){
				dealDataBase(node);
				node = node->first_node();
			}else if(strcmp(node->name(), "table") == 0){
				dealTable(node);
				node = node->next_sibling();
			}else{
				printf_s("read config error on DB param name = %s \n", node->name());
				node = node->next_sibling();
			}
		}
		doc.validate();
	}catch(parse_error & e) {
        std::cout << "Parse error: " << e.what() << std::endl << "At: " << e.where<char>() << std::endl;
    } catch(validation_error & e) {
        std::cout << "Validation error: " << e.what() << std::endl;
    }
	return true;
}

bool SysConfMgr::dealDataBase(xml_node<char> *node){
	std::string sql = "CREATE DATABASE `";
	auto attr = node->first_attribute();
	while(attr){
		if(strcmp(attr->name(), "name") == 0){
			sql += string(attr->value()) + "`;\n";
			mTables.insert(make_pair(mTables.size() + 1, sql));
			sql = "use `" + string(attr->value()) + "`;\n";
			mTables.insert(make_pair(mTables.size() + 1, sql));
		}else if(strcmp(attr->name(), "param") == 0){
			mTableParam = string(attr->value()) + ";\n";
		}else{
			printf_s("read config error on DB param name = %s \n", attr->name());
		}
		attr = attr->next_attribute();
	}
	return  true;
}

bool SysConfMgr::dealTable(xml_node<char> *node){
	std::string sql = "CREATE TABLE `";
	std::string primarykey = "";
	std::string keysql = "";
	std::string struct_s = "struct S";
	//解析表属性
	auto attr = node->first_attribute();
	while(attr){
		if(strcmp(attr->name(), "name") == 0){
			sql += string(attr->value()) + "` (\n";
			struct_s += string(attr->value()) + "{\n";
			mStructs.push_back(struct_s);
		}else if(strcmp(attr->name(), "primarykey") == 0){
			primarykey = attr->value();
			if(strcmp(attr->value(), "") != 0){
				keysql = "PRIMARY KEY (" + primarykey + ")";
			}
		}else{
			printf_s("read config error on Table attr name = %s \n", attr->name());
		}
		attr = attr->next_attribute();
	}

	//解析表字段
	auto node_column = node->first_node();
	while(node_column){
		SColumn column;
		if(strcmp(node_column->name(), "column") == 0){
			dealColumn(node_column, &column);
			sql += column.type;
			if(column.key && column.name != primarykey){
				if(keysql != "")
					keysql += ",\n";
				if(column.unique)
					keysql += "UNIQUE ";
				keysql+="KEY `" + column.name + "` (`" + column.name + "`)";
			}
		}else{
			printf_s("read config error on Table column name = %s \n", node->name());
		}
		node_column = node_column->next_sibling();
	}

	//处理收尾工作
	if(keysql == ""){
		sql[sql.size() - 2] = '\0';
	}else{
		sql += keysql;
	}
	sql += "\n) " + mTableParam;
	//存入sql池
	mTables.insert(make_pair(mTables.size() + 1, sql));
	mStructs.push_back("};\n");

	return true;
}

bool SysConfMgr::dealColumn(xml_node<char> *node, SColumn *column){
	//读取列属性
	auto attr = node->first_attribute();
	while(attr){
		if(strcmp(attr->name(), "name") == 0){
			column->name = attr->value();
		}else if(strcmp(attr->name(), "type") == 0){
			column->type = attr->value();
		}else if(strcmp(attr->name(), "size") == 0){
			column->size = attr->value();
		}else if(strcmp(attr->name(), "null") == 0){
			if(strcmp(attr->value(), "1") == 0)
				column->cnil = true;
		}else if(strcmp(attr->name(), "unique") == 0){
			if(strcmp(attr->value(), "1") == 0)
				column->unique = true;
		}else if(strcmp(attr->name(), "unsigned") == 0){
			if(strcmp(attr->value(), "1") == 0)
				column->unsign = true;
		}else if(strcmp(attr->name(), "key") == 0){
			if(strcmp(attr->value(), "1") == 0)
				column->key = true;
		}else{
			printf_s("read config error on column attr name = %s \n", attr->name());
		}
		attr = attr->next_attribute();
	}

	//分析列属性
	dbColumn(column);
	return true;
}

void SysConfMgr::dbColumn(SColumn *column){
	if(strcmp(column->type.c_str(), "int") == 0){
		if(strcmp(column->size.c_str(), "") == 0)
			column->type = "`" + column->name + "` int(11) ";
		else 
			column->type = "`" + column->name + "` int(" + column->size + ") ";
		if(column->unsign)
			column->type += "unsigned ";
		if(column->cnil)
			column->type += "NOT NULL DEFAULT '0',\n";
		else 
			column->type += "DEFAULT NULL,\n";
		mStructs.push_back("\tint " + column->name + ";\n");
	}else if(strcmp(column->type.c_str(), "string") == 0){
		if(strcmp(column->size.c_str(), "") == 0)
			column->type = "`" + column->name + "` varchar(255) ";
		else 
			column->type = "`" + column->name + "` varchar(" + column->size + ") ";
		if(column->cnil)
			column->type += "NOT NULL DEFAULT '',\n";
		else 
			column->type += "DEFAULT NULL,\n";
		mStructs.push_back("\tstring " + column->name + ";\n");
	}else if(strcmp(column->type.c_str(), "text") == 0){
		column->type = "`" + column->name + "` text ";
		if(column->cnil)
			column->type += "NOT NULL,\n";
		else 
			column->type += "DEFAULT NULL,\n";
		mStructs.push_back("\tstring " + column->name + ";\n");
	}else if(strcmp(column->type.c_str(), "bool") == 0){
		column->type = "`" + column->name + "` bit(1) ";
		if(column->cnil)
			column->type += "NOT NULL DEFAULT b'0',\n";
		else 
			column->type += "DEFAULT NULL,\n";
		mStructs.push_back("\tbool " + column->name + ";\n");
	}else if(strcmp(column->type.c_str(), "float") == 0){
		column->type = "`" + column->name + "` float ";
		if(column->unsign)
			column->type += "unsigned ";
		if(column->cnil)
			column->type += "NOT NULL DEFAULT '0',\n";
		else 
			column->type += "DEFAULT NULL,\n";
		mStructs.push_back("\tfloat " + column->name + ";\n");
	}else if(strcmp(column->type.c_str(), "double") == 0){
		column->type = "`" + column->name + "` double ";
		if(column->unsign)
			column->type += "unsigned ";
		if(column->cnil)
			column->type += "NOT NULL DEFAULT '0',\n";
		else 
			column->type += "DEFAULT NULL,\n";
		mStructs.push_back("\tdouble " + column->name + ";\n");
	}else if(strcmp(column->type.c_str(), "datetime") == 0){
		column->type = "`" + column->name + "` datetime ";
		if(column->cnil)
			column->type += "NOT NULL DEFAULT '0000-00-00 00:00:00',\n";
		else 
			column->type += "DEFAULT NULL,\n";
		mStructs.push_back("\tstring " + column->name + ";\n");
	}else{
		printf_s("db column type Unsupported！ type = %s \n", column->type.c_str());
	}
}

bool SysConfMgr::saveSqls2file(const std::string filename){
	return CReadConf::GetInstance()->writeFile(filename, SysConfMgr::writeSqls);
}

bool SysConfMgr::saveStructs2File(const std::string filename){
	return CReadConf::GetInstance()->writeFile(filename, SysConfMgr::writeStruct);
}

void SysConfMgr::writeSqls(FILE* fp){
	auto it = GetInstance()->mTables.begin();
	for(; it != GetInstance()->mTables.end(); ++it){
		fprintf_s(fp, "%d->%s", it->first, it->second.c_str());
	}
}

void SysConfMgr::writeStruct(FILE* fp){
	for(std::string str : GetInstance()->mStructs){
		fputs(str.c_str(), fp);
	}
}

#ifdef _DEBUG
void SysConfMgr::printSqls(){
	auto it = mTables.begin();
	for(;it!=mTables.end();++it){
		printf("%d  %s", it->first, it->second.c_str());
	}
	for(std::string str: mStructs){
		printf(str.c_str());
	}
}
#endif