#pragma once
#include <iostream>
#include <mysql.h>
#include <string>
#include <vector>
#include "message.h"

using namespace std;
class DatBase
{
public:
	DatBase() {

		mysql_init(&mysql);
		if (&mysql == nullptr) {
			cout << "Error: can't create MySQL-descriptor" << endl;
		}
		if (!mysql_real_connect(&mysql, "localhost", "root", "33mulido", "testdb", NULL, NULL, 0)) {
			cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
		}
		mysql_query(&mysql, "CREATE TABLE table_chat(id INT AUTO_INCREMENT PRIMARY KEY, from_ VARCHAR(255), text VARCHAR(255))");
	};

	~DatBase() {
		mysql_close(&mysql);
		system("Pause");
	}

	void insertValue(string from, string text) {
		string query = string("INSERT INTO table_chat(from_, text) values('") + from + string("','") + text + string("')");
		mysql_query(&mysql, query.c_str());
	}

	void showTable() {
		mysql_query(&mysql, "SELECT from_, text FROM table_chat");
		if (res = mysql_store_result(&mysql)) {
			while (row = mysql_fetch_row(res)) {
				for (i = 0; i < mysql_num_fields(res); i++) {
					cout << row[i] << "  ";
				}
				cout << endl;
			}
		}
		else
			cout << "Error " << mysql_error(&mysql);
	};

	vector<Message> returnMesVector() {
		vector<Message> messagesDB;
		mysql_query(&mysql, "SELECT from_, text FROM table_chat");
		if (res = mysql_store_result(&mysql)) {
			while (row = mysql_fetch_row(res)) {
				Message* mmm = new Message(row[0], row[1]);
				messagesDB.push_back(*mmm);
			}
		}
		else
			cout << "Error " << mysql_error(&mysql);
		return messagesDB;
	};

private:
	MYSQL mysql;
	MYSQL_RES* res = nullptr;
	MYSQL_ROW row = 0;
	int i = 0;
};

