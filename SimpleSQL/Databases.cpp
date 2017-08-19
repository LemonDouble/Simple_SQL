#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <functional>
#include "Databases.h"
using namespace std;
using std::cout;

void help();
void swap(string *index1,string *index2);


Table::Table(string _TableName, int _DataIndex) {
	TableName = new string;
	*TableName = _TableName;
	//Table���� �̸� �ϳ����� �����Ƿ�, �̸��� ���� �Ҵ� �޴´�.

	if (_DataIndex != 0) {
		for (int i = 0; i < _DataIndex; i++) {
			DataArr.push_back("NULL");
		}
	}
	//�̹� Record�� �Էµ� ���¿��� Table�� �߰� �����ϴ� ���, �߰��� Table�� �Էµ� Record �κ��� ��� �ȴ�. �� �κ��� "NULL"�̶� ���ڿ��� ä���ش�.
}
//Table�� ������.

Table::~Table(){
	delete TableName;
}
//Table�� �Ҹ���. ���� �Ҵ���� Table �̸��� �ݳ��Ѵ�.

string Table::GetTableName() {
	return *TableName;
}
//Table�� �̸��� return�Ѵ�.

void Table::InputData() {
	string temp;
	cout << this->GetTableName() << "���̺��� �� >> ";
	cin >> temp;
	DataArr.push_back(temp);
}
// input�� �޾� Table�� DataArr �迭 ���� ���� �����Ѵ�.

void Table::DeleteData(int _index) {
	DataArr.erase(DataArr.begin() + _index);
}
//index�� �޾� index�� ��ġ�ϴ� �����͸� �����.

bool Table::FindData(string _FindValues, int _Dataindex) {
	bool ValueIExist = false;
	//DATA�� ��ġ�ϴ� ���� �־����� �˷��� bool�� ����.

	for (int i = 0; i < _Dataindex; i++) {
		if (DataArr[i] == _FindValues) {
			//���� ��ġ�ϴ� �����Ͱ� ������
			ValueIExist = true;
			//DATA�� ��ġ�ϴ� ���� �־����Ƿ� ValuesExist ������ True�� �ٲٰ�
			cout << GetTableName() << "���̺��� ã���ô� ���� ��ġ�ϴ� ���� �߰��߽��ϴ�." << endl;
			cout << "ã���ô� ���ڵ��� �ε����� { " << i << " }�Դϴ�." << endl;
			cout << "----------------------------------------------------------------" << endl;
			//�ε����� ���. �ߺ��Ǵ� ���ڵ尡 ���� �� �����Ƿ� break;�� ������� �ʴ´�.
		}
	}

	if (ValueIExist) {
		//���� ��ġ�ϴ� �� ������
		return true;
		//true ����
	}
	else {
		//������
		return false;
		//false ����
	}
}

vector<string>* Table::GetDataArr() {
	return &DataArr;
}

Database::Database(string _DatabaseName) : TableIndex(0), DataIndex(0) {
	DatabaseName = new string;
	*DatabaseName = _DatabaseName;
};
//Database�� ������.

Database::~Database() {
	delete DatabaseName;
}
//Database�� �Ҹ���.

string Database::GetDatabaseName() {
	return *DatabaseName;
}
//Database �̸��� return�ϴ� �Լ�.

void Database::CreateTable(string _TableName) {
	Table *temp = new Table(_TableName, DataIndex);
	TableList.push_back(temp);
	TableIndex++;
}
//Table�� �߰��ϴ� �Լ�.

void Database::DescTables() {
	cout << "----------------------------" << endl;
	for (int i = 0; i < TableIndex; i++) {
		cout << TableList[i]->GetTableName() << endl;
	}
	cout << "----------------------------" << endl;
}
//Table�� �̸��� ���� return�ϴ� �Լ�.

void Database::InputValue() {

	for (int i = 0; i < TableIndex; i++) {
		TableList[i]->InputData();
	}
	DataIndex++;
}
//Table ���� �°� �����͸� �޾Ƽ� ����ִ´�.

void Database::PrintValue(string Tempstring) {

	Table *TempTable;
	int index;

	if (Tempstring == "*") {
		//���� ��ü�� ����ؾ� �� ������
		for (int i = 0; i < TableIndex; i++) {
			cout.width(10);
			//��� ���� 10ĭ���� �����Ѵ�.
			cout << TableList[i]->GetTableName();
		}
		//���̺��� ���� ����Ѵ�.
		cout << endl;
		//�ٹٲ�
		for (int i = 0; i < DataIndex; i++) {
			//��� �����͸� ����ؾ��ϹǷ� ������ �ε�����ŭ �ݺ�
			for (int j = 0; j < TableIndex; j++) {
				TempTable = TableList[j];
				// TableList���� ����ؾ� �� Table Ŭ������ �����͸� �޾ƿ�
				cout.width(10);
				cout << (*TempTable)[i];
			}
			//�� ���ڵ带 ���� ����Ѵ�.
			cout << endl;
		}
	}
	else {
		try {
			// Index�� string���� �޾����Ƿ�, stoi (string -> int) ��ȯ �� �Է°��� *, ���ڰ� �ƴϸ� ��Ÿ�� ������ ����.
			// �̸� �ذ��ϱ� ���� try-catch ��
			index = std::stoi(Tempstring);
			//stoi -> string�� int��

			if (index >= DataIndex || index < 0) {
				cout << "INDEX�� �߸� �ԷµǾ����ϴ�. Ȯ�� �ٶ��ϴ�." << endl;
				//index�� ���� ����ִ� �����ͺ��� ���ų�, ������� Ʋ������ ����Ѵ�.
			}
			else {
				//�׷��� �ʴٸ�
					for (int i = 0; i < TableIndex; i++) {
					cout.width(10);
					cout << TableList[i]->GetTableName();
				}
				//Table�� ��� ����Ѵ�.
				cout << endl;
				for (int i = 0; i < TableIndex; i++) {
					cout.width(10);
					TempTable = TableList[i];
					cout << (*TempTable)[index];
				}
				//�ش� Index�� Record�� ����Ѵ�.
				cout << endl;
			}
		}
		catch(std::invalid_argument&){
			//���� �Ű������� *, ���ڰ� �ƴ϶�� ������ ����Ѵ�.
			cout << "Printvalue�� �Ű� ������ �߸� �ԷµǾ����ϴ�. Ȯ�� �ٶ��ϴ�." << endl;
		}
	}
}

bool Database::FindValue(string _Tablename, string _FindValues) {

	bool TempReturn = false;
	// ���� ã�Ҵ��� �� ã�Ҵ��� �˷��� TempReturn �ӽ� ����

	if (_Tablename == "*") {
		//���� �Ű������� *�̶��
		for (int FindTableIndex = 0; FindTableIndex < TableIndex; FindTableIndex++) {
			//Table�� ��� ���鼭
			if (TableList[FindTableIndex]->FindData(_FindValues, DataIndex)) {
				//Data�� ã�´�.
				TempReturn = true;
				//���� ��ġ�ϴ� �����Ͱ� �ִٸ� true���� �����Ѵ�.
			}
		}
	}
	else {
		//�� �ܶ��
		for (int FindTableIndex = 0; FindTableIndex < TableIndex; FindTableIndex++) {
			//Table�� ��� ���鼭
			if (TableList[FindTableIndex]->GetTableName() == _Tablename) {
				//��ġ�ϴ� ���̺��� ������
				if (TableList[FindTableIndex]->FindData(_FindValues, DataIndex)) {
					//�� ���̺��� Data�� ã�´�.
					TempReturn = true;
					//���� ��ġ�ϴ� �����Ͱ� �ִٸ� true���� �����Ѵ�.
				}
			}
		}
	}

	if (TempReturn) {
		return true;
		//���� ��ġ�ϴ� �����Ͱ� ������ true�� ������
	}	
	else {
		return false;
		//���ٸ� false�� �����Ѵ�.
	}
}
// ã�� �������� index ����� Table::FindData �Լ� �ȿ� ���ǵǾ� �����Ƿ� ���⼱ ������ �ʿ䰡 ����.

string Database::FindChangeData(string _Tablename, string _strIndex) {
	//������ �� ������ �ϱ� ��, ���̺��� �ε����� �޾Ƽ� �ش� ���ڵ带 ������ش�.
	int index;
	bool TempReturn = false;

	try {
		//string index�� ���� �̿��� ���ڰ� ���� �� ��Ÿ�� ������ ����� try-catch ��
		index = std::stoi(_strIndex);
		//string -> int

		if (index >= DataIndex || index < 0) {
			cout << "Index ���� �߸� �ԷµǾ����ϴ�. Ȯ�� �ٶ��ϴ�." << endl;
			//�ε����� ���� �� �����Ͱ����� ���ų� ������� ���� ���
		}
		else {
			for (int FindTableindex = 0; FindTableindex < TableIndex; FindTableindex++) {
				//���̺��� ó������ ������ ���鼭
				if (TableList[FindTableindex]->GetTableName() == _Tablename) {
					//���� ���̺��� ��ġ�ϴ� ���̺��� ã�Ҵٸ�
					TempReturn = true;
					// ���� ã�����Ƿ� Tempreturn�� true��
					// (index >= DataIndex || index < 0) ���� �̻��� index�� �ɷ����Ƿ�, �� ������ ��������
					// ������ �����ϴ� �ε����̴�.
					return (*(TableList[FindTableindex]))[index];
					// �ش� Data�� return
				}
			}
		}
	}
	catch (std::invalid_argument&) {
		cout << "Index���� ������ �ƴմϴ�. Ȯ�� �ٶ��ϴ�." << endl;
	}

	return "ERROR";
	//�ش� �����͸� ã�� �� ������ "ERROR"�̶� string�� return�Ѵ�.
}

void Database::ChangeValue(string _Tablename, string _index, string _ChangeValue) {

	bool TempFind = false;
	int index;
	//main_code.cpp����, ChangeValue �Լ��� FindChangeData �Լ��� ���� ã���� ���� ���ư��� ������,
	//�Ű����� index�� �������� ����ȴ�. ���� try-catch ���� ������� �ʾҴ�.
	index = stoi(_index);

	for (int FindTableindex = 0; FindTableindex < TableIndex; FindTableindex++) {
		//���̺��� ó������ ������ ���鼭
		if (TableList[FindTableindex]->GetTableName() == _Tablename) {
			//Table��� ������ ���̺��� ã����
			TempFind = true;
			//���� ã�����Ƿ� true�� �����Ѵ�. (index�� FindChangeData���� ���� ������ ����ǹǷ�)
			(*(TableList[FindTableindex]))[index] = _ChangeValue;
			//�ش� ���̺�, �ε����� ChangeData�Լ��� ȣ���� ���� �ٲ۴�.
			break;
			//���� �ٲ����Ƿ� break������ �������� ������.
		}
	}
	if (!(TempFind)) {
		//���� ���� ã�� �� �ߴٸ� ���� ���
		cout << "��ġ�ϴ� ���̺��� ã�� �� �������ϴ�." << endl;
	}

}

void Database::DeleteValue(string _index) {
	//�ε����� �޾Ƽ� �ش� ���ڵ带 ��ü ����.
	int index;

	try {
		index = std::stoi(_index);
		if (index >= DataIndex || index < 0) {
			cout << "Index ���� �߸� �ԷµǾ����ϴ�. Ȯ�� �ٶ��ϴ�." << endl;
		}
		else {
			for (int i = 0; i < TableIndex; i++) {
				//���̺�� �ѹ���
				TableList[i]->DeleteData(index);
				//Deletedata �Լ��� ȣ���� �ش� index�� �����͸� �����.
			}
			DataIndex--;
			//�����͸� �ϳ� �������Ƿ� ������ ������ �ϳ� ���δ�.
		}
	}
	catch(std::invalid_argument&){
		cout << "Index���� ������ �ƴմϴ�. Ȯ�� �ٶ��ϴ�." << endl;
	}

}

void Database::STD_Sort(string _TableName) {
	clock_t begin, end;
	begin = clock();
	string *TempArray = new string[DataIndex];
	int *ChangeIndexArray = new int[DataIndex];
	int *INT_TempArray;
	int index;
	bool TableExist = false;
	bool INT_string = false;

	for (int i = 0; i < TableIndex; i++) {
		if (TableList[i]->GetTableName() == _TableName) {
			//Table�� ���鼭 ��ġ�ϴ� ���̺� ���� �ִ��� ã�´�.
			index = i;
			TableExist = true;
			break;
		}
	}

	if (TableExist) {
		//���� ���̺��� ������

		try {
			INT_TempArray = new int[DataIndex];
			for (int i = 0; i < DataIndex; i++) {
				INT_TempArray[i] = stoi((*TableList[index])[i]);
			}
			INT_string = true;
		}
		catch(std::invalid_argument&){
			delete[] INT_TempArray;
			INT_string = false;
			INT_TempArray = nullptr;
		}
		for (int i = 0; i < DataIndex; i++) {
			TempArray[i] = (*TableList[index])[i];
		}
		// ���� �迭�� TempArray�� �ű�

		if (INT_string) {
			string TempString;
			cout << "���� �迭�Դϴ�. ������������ �����Ͻðڽ��ϱ�? (Y/N) >> ";
			cin >> TempString;

			transform(TempString.begin(), TempString.end(), TempString.begin(), toupper);
			if (TempString == "YES" || TempString == "Y") {
				sort(INT_TempArray, INT_TempArray + DataIndex,greater<int>());
				// �׸��� ���� �迭�� Sort (int), ��������
			}
			else {
				sort(INT_TempArray, INT_TempArray + DataIndex);
				// �׸��� ���� �迭�� Sort (int), ��������
			}
		}
		else {
			sort((*TableList[index]->GetDataArr()).begin(), (*TableList[index]->GetDataArr()).end());
			// �׸��� ���� �迭�� Sort (string)
		}


		for (int i = 0; i < DataIndex; i++) {
			for (int j = 0; j < DataIndex; j++) 
				if (INT_string) {
					if (INT_TempArray[i] == stoi((*TableList[index])[j])) {
						ChangeIndexArray[i] = j;
						break;
						//int �迭�϶�
					}
				}
				else {
					if (TempArray[i] == (*TableList[index])[j]) {
						ChangeIndexArray[i] = j;
						break;
						//string �迭�϶�
				}
			}
		}
		// �׸��� ���� �迭�� ó�� �迭�� ���Ͽ� Index�� ��� �ٲ�������� ChangeIndexArray�� �ִ´�.

		for (int i = 0; i < TableIndex; i++) {
			if (i == index && !INT_string) {
				continue;
			}
			else {
				for (int j = 0; j < DataIndex; j++) {
					TempArray[j] = (*TableList[i])[j];
				}
				(*(*TableList[i]).GetDataArr()).clear();
				// ���͸� �����

				for (int j = 0; j < DataIndex; j++) {
					(*(*TableList[i]).GetDataArr()).push_back(TempArray[ChangeIndexArray[j]]);
					//ChangeIndexArray�� �ִ� ������� ���͸� ä��
				}
			}
		}
	}
	else {
		cout << "��ġ�ϴ� ���̺��� �����ϴ�." << endl;
	}

	delete[] TempArray;
	delete[] ChangeIndexArray;
	
	if (INT_TempArray != nullptr) {
		delete[] INT_TempArray;
	}
	
	end = clock();

	cout << "���� �Ϸ�. ����ð� = < " << ((end - begin) / CLOCKS_PER_SEC) << " > sec"<<endl;
}



DatabaseArr::DatabaseArr() :DatabaseIndex(0) {};
//�����ͺ��̽� �迭�� ������

DatabaseArr::~DatabaseArr() {
	for (int i = 0; i < DatabaseIndex; i++) {
		delete DataList[i];
	}
}
//�����ͺ��̽� �迭�� �Ҹ���


void DatabaseArr::CreateDatabase(string _DatabaseName) {
	Database *temp = new Database(_DatabaseName);
	//DatabaseName�� ������ Database�� ���� �Ҵ� �޴´�.
	DataList.push_back(temp);
	//���� �Ҵ���� Database�� Vector�� ���� �ִ´�.
	DatabaseIndex++;
	//�����ͺ��̽��� ������ �ϳ� �߰���Ų��.
}

int DatabaseArr::DataBaseCount() {
	return DatabaseIndex;
	//Database ������ return �ϴ� �Լ�.
}

Database* DatabaseArr::FindDatabase(string _DatabaseName) {
	for (int i = 0; i < DatabaseIndex; i++) {
		if (DataList[i]->GetDatabaseName() == _DatabaseName)
			return DataList[i];
		//Database��� ��ġ�ϴ� String ã�� ��쿡�� �� �����͸� return�Ѵ�.
	}
	
	cout << "��ġ�ϴ� ���̺��� ã�� �� �������ϴ�." << endl;
	return nullptr;
	//���н� nullptr�� return�Ѵ�.
}
//DATABASE �̸��� �޾� DATABASE �̸��� ��ġ�ϴ� �����͸� return�Ѵ�.

void DatabaseArr::DescDatabases() {
	cout << "----------------------------" << endl;
	for (int i = 0; i < DatabaseIndex; i++) {
		cout << DataList[i]->GetDatabaseName() << endl;
	}
	cout << "----------------------------" << endl;
}
//Database �̸��� ���� ����ϴ� �Լ�.

void help() {
	cout << "HELP ��ɾ��Դϴ�. ��� ��ɾ ����մϴ�." << endl;
	cout << "CREATE <DATABASE ��> -> DATABASE �� �´� �����ͺ��̽��� ����ϴ�." << endl;
	cout << "DATABASECOUNT -> DATABASE�� ������ ����մϴ�." << endl;
	cout << "DESCDATABASES -> DATABASE���� ���� ����մϴ�" << endl;
	/*
	cout << "SAVE -> ���ݱ��� �Է��� �����͸� ���� \"savedata.txt\" ���Ͽ� �����մϴ�." << endl;
	cout << "LOAD -> \"savedata.txt\"���Ͽ��� �����͸� �о�, �����ͺ��̽��� ��� �����ϰ� ����ϴ�." << endl;
	*/
	cout << "USE <DATABASE ��> -> DATABASE�� �´� �����ͺ��̽��� ����մϴ�." << endl;
	cout << "(USE ��� ��) EXIT -> �����ͺ��̽� ����� �����ϰ� �ʱ� ȭ������ ���ư��ϴ�." << endl;
	cout << "(USE ��� ��) CREATETABLE <TABLE ��> -> TABLE �� �´� ���̺��� ����մϴ�." << endl;
	cout << "(USE ��� ��) DESCTABLES -> �� DATABASE�� �ִ� TABLE���� ���� ����մϴ�." << endl;
	cout << "(USE ��� ��) INPUTVALUE -> RECORD �� ���� �Է��մϴ�." << endl;
	cout << "(USE ��� ��) PRINTVALUE <����� �������� INDEX> -> �ش� �ε����� ������ �ִ� ���ڵ带 ����մϴ�." << endl;
	cout << "(USE ��� ��) FINDVALUE  <ã�� ���̺� ��> <ã�� ������> -> �ش� ���̺��� �ش� �����Ϳ� ��ġ�ϴ� ���ڵ��� �ε����� ���� ����մϴ�." << endl;
	cout << "(USE ��� ��) CHANGEVALUE <������ �����Ͱ� �ִ� TABLE ��> <������ �����Ͱ� �ִ� INDEX> -> TABLE��� INDEX�� ��ġ�ϴ� ���� �ִ� �����͸� �����մϴ�." << endl;
	cout << "(USE ��� ��) DELETEVALUE <������ �ε��� ��ȣ> -> INDEX�� ��ġ�ϴ� ���ڵ带 �����մϴ�." << endl;
	cout << "(USE ��� ��) SORT <������ �� ���̺� ��> -> �� ���̺��� �������� �����͸� �����մϴ�." << endl;
}