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

//���� ��� �Լ�
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
	//���̺��� �̸��� �����ϴ� �Լ�
	void InputData();
	//���̺� �ϳ��� �����͸� ����ִ� �Լ�.
	bool FindData(string,int);
	//������ ���� �Ű������� �޾� ��ġ�ϴ� �ε������� �ݳ�.
	void DeleteData(int);
	string& operator[] (int idx){
		return DataArr[idx];
	}
	vector<string>* GetDataArr();
};
//�̸�/��ȭ��ȣ/����ó ���� ���̺��� �ϳ� ���涧���� ��ü�� �ϳ��� �����Ǵ� Table Ŭ����.


class Database {
	string *DatabaseName;
	vector <Table*> TableList;
	int TableIndex;
	//���ݱ��� �Էµ� Table�� ����
	int DataIndex;
	//���ݱ��� �Էµ� Record�� ����
public:

	Database(string _DatabaseName);
	~Database();

	string GetDatabaseName();
	//�����ͺ��̽��� �̸��� �����ϴ� �Լ�
	void CreateTable(string);
	//���̺��� �߰��ϴ� �Լ�
	void DescTables();
	//���ݱ��� �߰��� ��� ���̺��� ����ϴ� �Լ�.
	void InputValue();
	//�� ���ڵ带 �߰��ϴ� �Լ�.
	void PrintValue(string);
	//�ε����� �´� ���ڵ带 ����ϴ� �Լ�. -1 �Է½�	��ü ���.
	bool FindValue(string,string);
	//ã�� ���̺�� ������ ��������, ���ڵ� ��ȣ�� �������ش�.
	string FindChangeData(string, string);
	//���̺�� �ε����� �޾� �����͸� �������ش�.
	void ChangeValue(string,string, string);
	//���̺�� �ε���, ��� ���� �����͸� �޾� ���� �����Ѵ�.
	void DeleteValue(string);
	//���̺�� �ε����� �޾� ���� �����Ѵ�.
	void STD_Sort(string);
	//������ ���� Table ���� �޾Ƽ� �� Table�� �������� �����Ѵ�.
};
//�����ͺ��̽� �ϳ��� ��ü �ϳ��� �����Ǵ� Database Ŭ����.


class DatabaseArr {
	vector<Database*> DataList;
	//STL �����̳� ���͸� �����, Database�� ������ ���� �迭
	int DatabaseIndex;
	//���� �� ���� �����ͺ��̽��� ����Ǿ� �ִ����� ������ DatabaseIndex ����
public:
	DatabaseArr();
	~DatabaseArr();

	void CreateDatabase(string);
	//�����ͺ��̽����� �Ű������� �޾�, �����ͺ��̽� Ŭ������ ������ �ִ� �Լ�.
	int DataBaseCount();
	//�����ͺ��̽� ������ �� ���� �˷��ִ� �Լ�
	Database* FindDatabase(string);
	//�����ͺ��̽����� �Է¹����� �����ͺ��̽��� �ּҸ� ������
	void DescDatabases();
	//��� �����ͺ��̽����� ����ϴ� �Լ�.
};