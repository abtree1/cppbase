#include<iostream>
#include<fstream>
#include<string>
#include "msg.pb.h"
using namespace std;

void insert_person(tutorial::AddressBook& address_book) {
	//封装消息数据
	tutorial::Person* person = address_book.add_person();
	person->set_name("Zhang3");
	person->set_id(1);
	person->set_email("test@resr.com");
	tutorial::Person_PhoneNumber* phone1 = person->add_phone();
	phone1->set_number("123");
	phone1->set_type(tutorial::Person_PhoneType_MOBILE);
	tutorial::Person_PhoneNumber* phone2 = person->add_phone();
	phone2->set_number("456");
	phone2->set_type(tutorial::Person_PhoneType_HOME);
}

void print_person(tutorial::AddressBook& address_book) {
	//解析消息数据
	for (int i = 0; i < address_book.person_size(); i++) {
		const tutorial::Person& person = address_book.person(i);
		cout << "Person Id: " << person.id() << endl;
		cout << "Person Name: " << person.name() << endl;
		if (person.has_email())
			cout << "Person Email: " << person.email() << endl;

		for (int j = 0; j < person.phone_size(); j++) {
			const tutorial::Person::PhoneNumber& phone = person.phone(j);
			switch (phone.type())
			{
			case tutorial::Person_PhoneType_HOME:
				cout << "Home Phone: ";
				break;
			case tutorial::Person_PhoneType_MOBILE:
				cout << "MOBILE Phone: ";
				break;
			case tutorial::Person_PhoneType_WORK:
				cout << "Work Phone: ";
				break;
			}
			cout << phone.number() << endl;
		}
	}
}


int main(int argc, char* argv[]) {
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	tutorial::AddressBook address_book;
	insert_person(address_book);
	string buff = address_book.SerializeAsString();
	address_book.Clear();
	address_book.ParseFromString(buff);
	print_person(address_book);

	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();

	//强制让程序不退出
	for (;;) {}

	return 0;
}