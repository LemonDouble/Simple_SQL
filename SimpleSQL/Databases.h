#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include "Databases.h"
using namespace std;

class DatabaseArr;

void help();
void swap(string*, string*);

//도움말 출력 함수
/*
void Save(DatabaseArr &Savedata);
void Load(DatabaseArr &Loaddata);
*/


class Table {

	string *TableName;
	vector<string> DataArr;

public:
	Table(string _TableName, int _DataIndex);
	~Table();

	string GetTableName();
	//테이블의 이름을 리턴하는 함수
	void InputData();
	//테이블 하나에 데이터를 집어넣는 함수.
	bool FindData(string,int);
	//데이터 값을 매개변수로 받아 일치하는 인덱스값을 반납.
	void DeleteData(int);
	string& operator[] (int idx){
		return DataArr[idx];
	}
	vector<string>* GetDataArr();
};
//이름/전화번호/연락처 같은 테이블이 하나 생길때마다 객체가 하나씩 생성되는 Table 클래스.


class Database {
	string *DatabaseName;
	vector <Table*> TableList;
	int TableIndex;
	//지금까지 입력된 Table의 개수
	int DataIndex;
	//지금까지 입력된 Record의 개수
public:

	Database(string _DatabaseName);
	~Database();

	string GetDatabaseName();
	//데이터베이스의 이름을 리턴하는 함수
	void CreateTable(string);
	//테이블을 추가하는 함수
	void DescTables();
	//지금까지 추가된 모든 테이블을 출력하는 함수.
	void InputValue();
	//한 레코드를 추가하는 함수.
	void PrintValue(string);
	//인덱스에 맞는 레코드를 출력하는 함수. -1 입력시	전체 출력.
	bool FindValue(string,string);
	//찾을 테이블과 문장을 바탕으로, 레코드 번호를 리턴해준다.
	string FindChangeData(string, string);
	//테이블과 인덱스를 받아 데이터를 리턴해준다.
	void ChangeValue(string,string, string);
	//테이블과 인덱스, 대신 넣을 데이터를 받아 값을 수정한다.
	void DeleteValue(string);
	//테이블과 인덱스를 받아 값을 삭제한다.
	void STD_Sort(string);
	//정렬할 기준 Table 명을 받아서 그 Table을 기준으로 정렬한다.
};
//데이터베이스 하나당 객체 하나가 생성되는 Database 클래스.


class DatabaseArr {
	vector<Database*> DataList;
	//STL 컨테이너 벡터를 사용한, Database를 저장할 동적 배열
	int DatabaseIndex;
	//현재 몇 개의 데이터베이스가 저장되어 있는지를 저장할 DatabaseIndex 변수
public:
	DatabaseArr();
	~DatabaseArr();

	void CreateDatabase(string);
	//데이터베이스명을 매개변수로 받아, 데이터베이스 클래스를 생성해 주는 함수.
	int DataBaseCount();
	//데이터베이스 개수가 몇 갠지 알려주는 함수
	Database* FindDatabase(string);
	//데이터베이스명을 입력받으면 데이터베이스의 주소를 리턴함
	void DescDatabases();
	//모든 데이터베이스명을 출력하는 함수.
};