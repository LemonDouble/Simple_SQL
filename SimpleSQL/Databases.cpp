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
	//Table마다 이름 하나씩을 가지므로, 이름을 동적 할당 받는다.

	if (_DataIndex != 0) {
		for (int i = 0; i < _DataIndex; i++) {
			DataArr.push_back("NULL");
		}
	}
	//이미 Record가 입력된 상태에서 Table을 추가 생성하는 경우, 추가된 Table의 입력된 Record 부분은 비게 된다. 그 부분을 "NULL"이란 문자열로 채워준다.
}
//Table의 생성자.

Table::~Table(){
	delete TableName;
}
//Table의 소멸자. 동적 할당받은 Table 이름을 반납한다.

string Table::GetTableName() {
	return *TableName;
}
//Table의 이름을 return한다.

void Table::InputData() {
	string temp;
	cout << this->GetTableName() << "테이블의 값 >> ";
	cin >> temp;
	DataArr.push_back(temp);
}
// input을 받아 Table의 DataArr 배열 가장 끝에 저장한다.

void Table::DeleteData(int _index) {
	DataArr.erase(DataArr.begin() + _index);
}
//index를 받아 index와 일치하는 데이터를 지운다.

bool Table::FindData(string _FindValues, int _Dataindex) {
	bool ValueIExist = false;
	//DATA와 일치하는 값이 있었는지 알려줄 bool형 변수.

	for (int i = 0; i < _Dataindex; i++) {
		if (DataArr[i] == _FindValues) {
			//만약 일치하는 데이터가 있으면
			ValueIExist = true;
			//DATA와 일치하는 값이 있었으므로 ValuesExist 변수를 True로 바꾸고
			cout << GetTableName() << "테이블에서 찾으시는 값과 일치하는 값을 발견했습니다." << endl;
			cout << "찾으시는 레코드의 인덱스는 { " << i << " }입니다." << endl;
			cout << "----------------------------------------------------------------" << endl;
			//인덱스를 출력. 중복되는 레코드가 있을 수 있으므로 break;는 사용하지 않는다.
		}
	}

	if (ValueIExist) {
		//만약 일치하는 값 있으면
		return true;
		//true 리턴
	}
	else {
		//없으면
		return false;
		//false 리턴
	}
}

vector<string>* Table::GetDataArr() {
	return &DataArr;
}

Database::Database(string _DatabaseName) : TableIndex(0), DataIndex(0) {
	DatabaseName = new string;
	*DatabaseName = _DatabaseName;
};
//Database의 생성자.

Database::~Database() {
	delete DatabaseName;
}
//Database의 소멸자.

string Database::GetDatabaseName() {
	return *DatabaseName;
}
//Database 이름을 return하는 함수.

void Database::CreateTable(string _TableName) {
	Table *temp = new Table(_TableName, DataIndex);
	TableList.push_back(temp);
	TableIndex++;
}
//Table을 추가하는 함수.

void Database::DescTables() {
	cout << "----------------------------" << endl;
	for (int i = 0; i < TableIndex; i++) {
		cout << TableList[i]->GetTableName() << endl;
	}
	cout << "----------------------------" << endl;
}
//Table의 이름을 전부 return하는 함수.

void Database::InputValue() {

	for (int i = 0; i < TableIndex; i++) {
		TableList[i]->InputData();
	}
	DataIndex++;
}
//Table 수에 맞게 데이터를 받아서 집어넣는다.

void Database::PrintValue(string Tempstring) {

	Table *TempTable;
	int index;

	if (Tempstring == "*") {
		//만약 전체를 출력해야 할 떄에는
		for (int i = 0; i < TableIndex; i++) {
			cout.width(10);
			//출력 폭을 10칸으로 고정한다.
			cout << TableList[i]->GetTableName();
		}
		//테이블을 전부 출력한다.
		cout << endl;
		//줄바꿈
		for (int i = 0; i < DataIndex; i++) {
			//모든 데이터를 출력해야하므로 데이터 인덱스만큼 반복
			for (int j = 0; j < TableIndex; j++) {
				TempTable = TableList[j];
				// TableList에서 출력해야 될 Table 클래스의 포인터를 받아옴
				cout.width(10);
				cout << (*TempTable)[i];
			}
			//한 레코드를 전부 출력한다.
			cout << endl;
		}
	}
	else {
		try {
			// Index를 string으로 받았으므로, stoi (string -> int) 변환 시 입력값이 *, 숫자가 아니면 런타임 에러가 난다.
			// 이를 해결하기 위한 try-catch 문
			index = std::stoi(Tempstring);
			//stoi -> string을 int로

			if (index >= DataIndex || index < 0) {
				cout << "INDEX가 잘못 입력되었습니다. 확인 바랍니다." << endl;
				//index가 현재 들어있는 데이터보다 많거나, 음수라면 틀렸음을 출력한다.
			}
			else {
				//그렇지 않다면
					for (int i = 0; i < TableIndex; i++) {
					cout.width(10);
					cout << TableList[i]->GetTableName();
				}
				//Table을 모두 출력한다.
				cout << endl;
				for (int i = 0; i < TableIndex; i++) {
					cout.width(10);
					TempTable = TableList[i];
					cout << (*TempTable)[index];
				}
				//해당 Index의 Record를 출력한다.
				cout << endl;
			}
		}
		catch(std::invalid_argument&){
			//만약 매개변수가 *, 숫자가 아니라면 에러를 출력한다.
			cout << "Printvalue의 매개 변수가 잘못 입력되었습니다. 확인 바랍니다." << endl;
		}
	}
}

bool Database::FindValue(string _Tablename, string _FindValues) {

	bool TempReturn = false;
	// 값을 찾았는지 안 찾았는지 알려줄 TempReturn 임시 변수

	if (_Tablename == "*") {
		//만약 매개변수가 *이라면
		for (int FindTableIndex = 0; FindTableIndex < TableIndex; FindTableIndex++) {
			//Table을 모두 돌면서
			if (TableList[FindTableIndex]->FindData(_FindValues, DataIndex)) {
				//Data를 찾는다.
				TempReturn = true;
				//만약 일치하는 데이터가 있다면 true값을 리턴한다.
			}
		}
	}
	else {
		//그 외라면
		for (int FindTableIndex = 0; FindTableIndex < TableIndex; FindTableIndex++) {
			//Table을 모두 돌면서
			if (TableList[FindTableIndex]->GetTableName() == _Tablename) {
				//일치하는 테이블이 있으면
				if (TableList[FindTableIndex]->FindData(_FindValues, DataIndex)) {
					//그 테이블에서 Data를 찾는다.
					TempReturn = true;
					//만약 일치하는 데이터가 있다면 true값을 리턴한다.
				}
			}
		}
	}

	if (TempReturn) {
		return true;
		//만약 일치하는 데이터가 있으면 true를 리턴을
	}	
	else {
		return false;
		//없다면 false를 리턴한다.
	}
}
// 찾은 데이터의 index 출력은 Table::FindData 함수 안에 정의되어 있으므로 여기선 정의할 필요가 없다.

string Database::FindChangeData(string _Tablename, string _strIndex) {
	//데이터 값 수정을 하기 전, 테이블명과 인덱스를 받아서 해당 레코드를 출력해준다.
	int index;
	bool TempReturn = false;

	try {
		//string index가 숫자 이외의 문자가 들어올 때 런타임 에러를 잡아줄 try-catch 문
		index = std::stoi(_strIndex);
		//string -> int

		if (index >= DataIndex || index < 0) {
			cout << "Index 값이 잘못 입력되었습니다. 확인 바랍니다." << endl;
			//인덱스가 지금 들어간 데이터값보다 많거나 음수라면 에러 출력
		}
		else {
			for (int FindTableindex = 0; FindTableindex < TableIndex; FindTableindex++) {
				//테이블을 처음부터 끝까지 돌면서
				if (TableList[FindTableindex]->GetTableName() == _Tablename) {
					//만약 테이블명과 일치하는 테이블을 찾았다면
					TempReturn = true;
					// 값을 찾았으므로 Tempreturn을 true로
					// (index >= DataIndex || index < 0) 에서 이상한 index를 걸렀으므로, 이 루프로 들어왔으면
					// 실제로 존재하는 인덱스이다.
					return (*(TableList[FindTableindex]))[index];
					// 해당 Data를 return
				}
			}
		}
	}
	catch (std::invalid_argument&) {
		cout << "Index값이 정수가 아닙니다. 확인 바랍니다." << endl;
	}

	return "ERROR";
	//해당 데이터를 찾지 못 했으면 "ERROR"이란 string을 return한다.
}

void Database::ChangeValue(string _Tablename, string _index, string _ChangeValue) {

	bool TempFind = false;
	int index;
	//main_code.cpp에서, ChangeValue 함수는 FindChangeData 함수가 값을 찾았을 때만 돌아가기 때문에,
	//매개변수 index는 숫자임이 보장된다. 따라서 try-catch 문은 사용하지 않았다.
	index = stoi(_index);

	for (int FindTableindex = 0; FindTableindex < TableIndex; FindTableindex++) {
		//테이블을 처음부터 끝까지 돌면서
		if (TableList[FindTableindex]->GetTableName() == _Tablename) {
			//Table명과 동일한 테이블을 찾으면
			TempFind = true;
			//값을 찾았으므로 true를 리턴한다. (index는 FindChangeData에서 정상 값임이 보장되므로)
			(*(TableList[FindTableindex]))[index] = _ChangeValue;
			//해당 테이블, 인덱스의 ChangeData함수를 호출해 값을 바꾼다.
			break;
			//값을 바꿨으므로 break문으로 루프에서 나간다.
		}
	}
	if (!(TempFind)) {
		//만약 값을 찾지 못 했다면 에러 출력
		cout << "일치하는 테이블을 찾을 수 없었습니다." << endl;
	}

}

void Database::DeleteValue(string _index) {
	//인덱스를 받아서 해당 레코드를 전체 삭제.
	int index;

	try {
		index = std::stoi(_index);
		if (index >= DataIndex || index < 0) {
			cout << "Index 값이 잘못 입력되었습니다. 확인 바랍니다." << endl;
		}
		else {
			for (int i = 0; i < TableIndex; i++) {
				//테이블당 한번씩
				TableList[i]->DeleteData(index);
				//Deletedata 함수를 호출해 해당 index의 데이터를 지운다.
			}
			DataIndex--;
			//데이터를 하나 지웠으므로 데이터 개수를 하나 줄인다.
		}
	}
	catch(std::invalid_argument&){
		cout << "Index값이 정수가 아닙니다. 확인 바랍니다." << endl;
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
			//Table을 돌면서 일치하는 테이블 명이 있는지 찾는다.
			index = i;
			TableExist = true;
			break;
		}
	}

	if (TableExist) {
		//만약 테이블이 있으면

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
		// 원래 배열을 TempArray로 옮김

		if (INT_string) {
			string TempString;
			cout << "숫자 배열입니다. 내림차순으로 정렬하시겠습니까? (Y/N) >> ";
			cin >> TempString;

			transform(TempString.begin(), TempString.end(), TempString.begin(), toupper);
			if (TempString == "YES" || TempString == "Y") {
				sort(INT_TempArray, INT_TempArray + DataIndex,greater<int>());
				// 그리고 원래 배열을 Sort (int), 내림차순
			}
			else {
				sort(INT_TempArray, INT_TempArray + DataIndex);
				// 그리고 원래 배열을 Sort (int), 오름차순
			}
		}
		else {
			sort((*TableList[index]->GetDataArr()).begin(), (*TableList[index]->GetDataArr()).end());
			// 그리고 원래 배열을 Sort (string)
		}


		for (int i = 0; i < DataIndex; i++) {
			for (int j = 0; j < DataIndex; j++) 
				if (INT_string) {
					if (INT_TempArray[i] == stoi((*TableList[index])[j])) {
						ChangeIndexArray[i] = j;
						break;
						//int 배열일때
					}
				}
				else {
					if (TempArray[i] == (*TableList[index])[j]) {
						ChangeIndexArray[i] = j;
						break;
						//string 배열일때
				}
			}
		}
		// 그리고 원래 배열과 처음 배열을 비교하여 Index가 어떻게 바뀌었는지를 ChangeIndexArray에 넣는다.

		for (int i = 0; i < TableIndex; i++) {
			if (i == index && !INT_string) {
				continue;
			}
			else {
				for (int j = 0; j < DataIndex; j++) {
					TempArray[j] = (*TableList[i])[j];
				}
				(*(*TableList[i]).GetDataArr()).clear();
				// 벡터를 비워줌

				for (int j = 0; j < DataIndex; j++) {
					(*(*TableList[i]).GetDataArr()).push_back(TempArray[ChangeIndexArray[j]]);
					//ChangeIndexArray에 있는 순서대로 벡터를 채움
				}
			}
		}
	}
	else {
		cout << "일치하는 테이블이 없습니다." << endl;
	}

	delete[] TempArray;
	delete[] ChangeIndexArray;
	
	if (INT_TempArray != nullptr) {
		delete[] INT_TempArray;
	}
	
	end = clock();

	cout << "정렬 완료. 수행시간 = < " << ((end - begin) / CLOCKS_PER_SEC) << " > sec"<<endl;
}



DatabaseArr::DatabaseArr() :DatabaseIndex(0) {};
//데이터베이스 배열의 생성자

DatabaseArr::~DatabaseArr() {
	for (int i = 0; i < DatabaseIndex; i++) {
		delete DataList[i];
	}
}
//데이터베이스 배열의 소멸자


void DatabaseArr::CreateDatabase(string _DatabaseName) {
	Database *temp = new Database(_DatabaseName);
	//DatabaseName을 가지는 Database를 동적 할당 받는다.
	DataList.push_back(temp);
	//동적 할당받은 Database를 Vector에 집어 넣는다.
	DatabaseIndex++;
	//데이터베이스의 개수를 하나 추가시킨다.
}

int DatabaseArr::DataBaseCount() {
	return DatabaseIndex;
	//Database 개수를 return 하는 함수.
}

Database* DatabaseArr::FindDatabase(string _DatabaseName) {
	for (int i = 0; i < DatabaseIndex; i++) {
		if (DataList[i]->GetDatabaseName() == _DatabaseName)
			return DataList[i];
		//Database명과 일치하는 String 찾은 경우에는 그 포인터를 return한다.
	}
	
	cout << "일치하는 테이블을 찾을 수 없었습니다." << endl;
	return nullptr;
	//실패시 nullptr을 return한다.
}
//DATABASE 이름을 받아 DATABASE 이름과 일치하는 포인터를 return한다.

void DatabaseArr::DescDatabases() {
	cout << "----------------------------" << endl;
	for (int i = 0; i < DatabaseIndex; i++) {
		cout << DataList[i]->GetDatabaseName() << endl;
	}
	cout << "----------------------------" << endl;
}
//Database 이름을 전부 출력하는 함수.

void help() {
	cout << "HELP 명령어입니다. 모든 명령어를 출력합니다." << endl;
	cout << "CREATE <DATABASE 명> -> DATABASE 명에 맞는 데이터베이스를 만듭니다." << endl;
	cout << "DATABASECOUNT -> DATABASE의 개수를 출력합니다." << endl;
	cout << "DESCDATABASES -> DATABASE명을 전부 출력합니다" << endl;
	/*
	cout << "SAVE -> 지금까지 입력한 데이터를 전부 \"savedata.txt\" 파일에 저장합니다." << endl;
	cout << "LOAD -> \"savedata.txt\"파일에서 데이터를 읽어, 데이터베이스를 사용 가능하게 만듭니다." << endl;
	*/
	cout << "USE <DATABASE 명> -> DATABASE명에 맞는 데이터베이스를 사용합니다." << endl;
	cout << "(USE 사용 후) EXIT -> 데이터베이스 사용을 종료하고 초기 화면으로 돌아갑니다." << endl;
	cout << "(USE 사용 후) CREATETABLE <TABLE 명> -> TABLE 명에 맞는 테이블을 출력합니다." << endl;
	cout << "(USE 사용 후) DESCTABLES -> 현 DATABASE에 있는 TABLE명을 전부 출력합니다." << endl;
	cout << "(USE 사용 후) INPUTVALUE -> RECORD 한 줄을 입력합니다." << endl;
	cout << "(USE 사용 후) PRINTVALUE <출력할 데이터의 INDEX> -> 해당 인덱스를 가지고 있는 레코드를 출력합니다." << endl;
	cout << "(USE 사용 후) FINDVALUE  <찾을 테이블 명> <찾을 데이터> -> 해당 테이블에서 해당 데이터와 일치하는 레코드의 인덱스를 전부 출력합니다." << endl;
	cout << "(USE 사용 후) CHANGEVALUE <수정할 데이터가 있는 TABLE 명> <수정할 데이터가 있는 INDEX> -> TABLE명과 INDEX가 일치하는 곳에 있는 데이터를 수정합니다." << endl;
	cout << "(USE 사용 후) DELETEVALUE <삭제할 인덱스 번호> -> INDEX와 일치하는 레코드를 삭제합니다." << endl;
	cout << "(USE 사용 후) SORT <기준이 될 테이블 명> -> 그 테이블을 기준으로 데이터를 정렬합니다." << endl;
}