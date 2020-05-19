#pragma once
#include <stdio.h> 
#include <stdio.h>
#include <stdlib.h>
#include "sqlite/sqlite3.h"
#include <string>
#include <ctime>
#include <chrono> // for time
#include <time.h>  /* time_t, struct tm, difftime, time, mktime */
#pragma warning(disable : 4996)
using namespace std;
class DatabaseHandler
{
public:
	DatabaseHandler() {};
	~DatabaseHandler() {};
	int Init();
	void CreateFirstTable();
	void FirstInsert();
	void FirstRead();
	void FirstMerge();
	void FirstDelete();
	void SelectAllFromTable(std::string tableName);
	void RunQuery(const char* c);
	void RunQueryString(std::string q);
	void FillTables(const char* c);
	void CreateUser(std::string name, std::string email, std::string pw);
	void Login(std::string name, std::string pw);
	void ListTables();
private:
	bool DbOpenCheck(int rc, sqlite3* db);
	bool DbTableCheck(int rc);
	bool DbRecordCheck(int rc);
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	const char* sql;
	const char* data = "Callback function called";
	static int callback(void* data, int argc, char** argv, char** azColName) {
		int i;
		fprintf(stderr, "%s: ", (const char*)data);

		for (i = 0; i < argc; i++) {
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}

		printf("\n");
		return 0;

	}
};
void DatabaseHandler::RunQuery(const char* c)
{
	rc = sqlite3_open("GameServer.db", &db);
	if (DbOpenCheck(rc, db)) //Check if we opened dp
	{
		rc = sqlite3_exec(db, c, callback, 0, &zErrMsg);
		DbTableCheck(rc);
	}
	sqlite3_close(db);
}
void DatabaseHandler::RunQueryString(std::string q)
{
	rc = sqlite3_open("GameServer.db", &db);
	sql = q.c_str();
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	DbRecordCheck(rc);
	sqlite3_close(db);
}
bool DatabaseHandler::DbOpenCheck(int rc, sqlite3* db)
{
	if (rc) {
		printf("%c[%dm__________________\n", 0x1B, 31);//Red
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return false;
	}
	else {
		printf("%c[%dm\n__________________\n", 0x1B, 32);//Green
		fprintf(stderr, "Opened database successfully\n");
		printf("%c[%dm", 0x1B, 39);//White
		return true;
	}
}
void DatabaseHandler::CreateUser(std::string name, std::string email, std::string pw)
{
	rc = sqlite3_open("GameServer.db", &db);
	/* Create SQL statement */
	/* Create SQL statement */
	const auto p1 = std::chrono::system_clock::now();
	std::time_t today_time = std::chrono::system_clock::to_time_t(p1);
	string x = "INSERT INTO User(name,email,pw, created_at) VALUES('";
	x += name;
	x += "','";
	x += email;
	x += "','";
	x += pw;
	x += "','";
	x += std::ctime(&today_time);
	x += "')";
	sql = x.c_str();
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	DbRecordCheck(rc);
	sqlite3_close(db);
}
void DatabaseHandler::Login(std::string name, std::string pw)
{
	rc = sqlite3_open("GameServer.db", &db);

	/* Create SQL statement */
	string x = "SELECT name,id from User WHERE name = ";
	x += '"' + name + '"' + " AND pw = " + '"' + pw + '"' + ";";
	//x += " AND pw = " + '"' + pw + '"' + ";";
	sql = x.c_str();
	/* Execute SQL statement */
	//rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	struct sqlite3_stmt* selectstmt;
	rc = sqlite3_prepare_v2(db, sql, -1, &selectstmt, NULL);
	if (rc == SQLITE_OK)
	{
		if (sqlite3_step(selectstmt) == SQLITE_ROW)
		{
			// record found
			printf("%c[%dm\n__________________\n", 0x1B, 32);//Green
			fprintf(stderr, "Nice login mate\n");
			printf("%c[%dm", 0x1B, 39);//White
		}
		else
		{
			// no record found
			printf("%c[%dm__________________\n", 0x1B, 31);//Red
			fprintf(stdout, "Wrong login info! :/\n");
			printf("%c[%dm", 0x1B, 39);//White
		}
	}
	sqlite3_finalize(selectstmt);
	sqlite3_close(db);
}
void DatabaseHandler::ListTables()
{
	rc = sqlite3_open("GameServer.db", &db);
	string x = "SELECT name FROM sqlite_master WHERE type='table'";
	sql = x.c_str();
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	DbRecordCheck(rc);
	sqlite3_close(db);
}
bool DatabaseHandler::DbTableCheck(int rc)
{
	if (rc != SQLITE_OK) {
		printf("%c[%dm__________________\n", 0x1B, 31);//Red
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		printf("%c[%dm", 0x1B, 39);//White
		sqlite3_free(zErrMsg);
		return false;
	}
	else {
		printf("%c[%dm\n__________________\n", 0x1B, 32);//Green
		fprintf(stdout, "Table created successfully\n");
		printf("%c[%dm", 0x1B, 39);//White
		return true;
	}
}
bool DatabaseHandler::DbRecordCheck(int rc)
{
	if (rc != SQLITE_OK) {
		printf("%c[%dm__________________\n", 0x1B, 31);//Red
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		printf("%c[%dm", 0x1B, 39);//White
		sqlite3_free(zErrMsg);
		return false;
	}
	else {
		printf("%c[%dm\n__________________\n", 0x1B, 32);//Green
		fprintf(stdout, "Operation done successfully\n");
		printf("%c[%dm", 0x1B, 39);//White
		return true;
	}
}
int DatabaseHandler::Init()
{
	//First connect to db file
	//Create if needed
	rc = sqlite3_open("GameServer.db", &db);
	if (DbOpenCheck(rc, db))
	{
		return 0;
	}
	sqlite3_close(db);
	/* Create SQL statement */

}
void DatabaseHandler::CreateFirstTable()
{
	//const char* sql;
	rc = sqlite3_open("GameServer.db", &db);
	sql = "CREATE TABLE COMPANY("  \
		"ID INT PRIMARY KEY     NOT NULL," \
		"NAME           TEXT    NOT NULL," \
		"AGE            INT     NOT NULL," \
		"ADDRESS        CHAR(50)," \
		"SALARY         REAL );" \
		"CREATE TABLE USER("  \
		"ID INT PRIMARY KEY     NOT NULL," \
		"NAME           TEXT    NOT NULL," \
		"AGE            INT     NOT NULL," \
		"ADDRESS        CHAR(50)," \
		"SALARY         REAL );";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	DbTableCheck(rc);
	sqlite3_close(db);
}
void DatabaseHandler::FirstInsert()
{
	rc = sqlite3_open("GameServer.db", &db);
	/* Create SQL statement */
	/* Create SQL statement */
	sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		"VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		"VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		"VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		"VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	DbRecordCheck(rc);
	sqlite3_close(db);
}
void DatabaseHandler::FirstRead()
{
	rc = sqlite3_open("GameServer.db", &db);

	/* Create SQL statement */
	sql = "SELECT * from COMPANY";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	DbRecordCheck(rc);
	sqlite3_close(db);
}
void DatabaseHandler::FirstMerge()
{
	printf("%c[%dmHELLO!\n", 0x1B, 32);
	printf("%c[%dmHELLO!\n", 0x1B, 97);
	rc = sqlite3_open("GameServer.db", &db);
	/* Create merged SQL statement */
	sql = "UPDATE COMPANY set SALARY = 25000.00 where ID=1; " \
		"SELECT * from COMPANY";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	DbRecordCheck(rc);
	sqlite3_close(db);
}
void DatabaseHandler::FirstDelete()
{
	/* Open database */
	rc = sqlite3_open("GameServer.db", &db);
	/* Create merged SQL statement */
	sql = "DELETE from COMPANY where ID=2; " \
		"SELECT * from COMPANY";
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	DbRecordCheck(rc);
	sqlite3_close(db);
}

void DatabaseHandler::SelectAllFromTable(std::string tableName)
{
	printf("%c[%dmTestailaan\n", 0x1B, 31);
	rc = sqlite3_open("GameServer.db", &db);
	if (DbOpenCheck(rc, db))
	{
		string temp1 = "SELECT * from " + tableName;
		char* kek = &temp1[0];
		sql = kek;//Convert string to char array
		rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
		DbRecordCheck(rc);
		//delete[] kek;
	}
	sqlite3_close(db);
}
