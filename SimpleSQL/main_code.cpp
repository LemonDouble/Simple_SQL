#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Databases.h"
using namespace std;

int main() {
	string TempString,TempString2,TempString3,TempString4;
	// 명령어를 입력받을 String형 TempString 변수
	string NowDatabase;
	// 현재 사용중인 Database를 표시하기 위한 String형 변수
	DatabaseArr Jusorok;
	// 데이터베이스 객체 선언
	Database *NowDatabasePTR;
	// USE 명령어 사용을 위한 NowDatabasePTR 포인터

	cout << "주소록 프로그램입니다. 명령어를 입력해 주십시오." << endl << "명령어를 모를 시, HELP 명령어 사용 가능합니다. 명령어는 대소문자를 구분하지 않습니다." << endl;

	while (1) {
		cout << ">> ";
		cin >> TempString;

		transform(TempString.begin(), TempString.end(), TempString.begin(), toupper);
		//소문자를 전부 대소문자로 바꾼다. HELP, Help, help 전부 HELP로 인식되도록 한다.

		if (TempString == "HELP")
			help();
		else if (TempString == "CREATE") {
			cout << "만들 DATABASE 명? >>  ";
			cin >> TempString;
			Jusorok.CreateDatabase(TempString);
			cout << '<' << TempString << '>' << "  DATABASE 생성됨" << endl;
		}
		else if (TempString == "DATABASECOUNT") {
			cout << "DATABASE 개수 : " << Jusorok.DataBaseCount() << "개" << endl;
		}
		else if (TempString == "DESCDATABASES") {
			Jusorok.DescDatabases();
		}
		/*
		else if (TempString == "SAVE") {
			Save(Jusorok);
		}
		else if (TempString == "LOAD") {
			Load(Jusorok);
		}
		*/
		else if (TempString == "USE") {
			NowDatabasePTR = nullptr;

			cout << "사용할 DATABASE 명? >> ";
			cin >> TempString;

			NowDatabasePTR = Jusorok.FindDatabase(TempString);

			if (NowDatabasePTR == nullptr) {
				cout << endl << TempString << " DATABASE 검색 실패. 확인 부탁드립니다." << endl;
			}
			else{
				cout << endl <<TempString << "을 사용합니다." << endl;
				NowDatabase = TempString;
				while (1) {
					cout << NowDatabase << " >> ";
					cin >> TempString;

					transform(TempString.begin(), TempString.end(), TempString.begin(), toupper);

					if (TempString == "EXIT") {
						cout << "EXIT 명령어 감지. 초기화면으로 돌아갑니다." << endl;
						break;
					}
					else if (TempString == "CREATETABLE") {
						cout << "만들 TABLE 명? >> ";
						cin >> TempString;

						NowDatabasePTR->CreateTable(TempString);

						cout << '<' << TempString << '>' << "  TABLE 생성됨" << endl;
					}
					else if (TempString == "DESCTABLES") {
						NowDatabasePTR->DescTables();
					}
					else if (TempString == "INPUTVALUE") {
						NowDatabasePTR->InputValue();
					}
					else if (TempString == "PRINTVALUE") {
						cout << "Print할 Record의 Index? (* 입력시 전체) >> ";
						cin >> TempString;
						NowDatabasePTR->PrintValue(TempString);
					}
					else if (TempString == "FINDVALUE") {
						cout << "찾을 테이블?(* 입력시 전체) >> ";
						cin >> TempString;
						cout << "찾을 데이터? >> ";
						cin >> TempString2;
						if(!(NowDatabasePTR->FindValue(TempString, TempString2))){
							cout << "데이터를 찾을 수 없었습니다." << endl;
						}
					}
					else if (TempString == "CHANGEVALUE") {
						cout << "수정할 데이터가 있는 테이블? >> ";
						cin >> TempString;
						cout << "수정할 데이터가 있는 인덱스? >> ";
						cin >> TempString2;
						TempString4 = NowDatabasePTR->FindChangeData(TempString, TempString2);

						if (TempString4 != "ERROR") {
							cout << "수정할 데이터는 { " << TempString4 << " } 값입니다." << endl;
							cout << "바꿀 데이터를 입력해 주십시오. (수정 원하지 않을 시 NO 입력) >> ";
							cin >> TempString3;
							if (!(TempString3 == "NO" || TempString3 == "no")) {
								NowDatabasePTR->ChangeValue(TempString, TempString2, TempString3);
							}
						}
					}
					else if (TempString == "DELETEVALUE") {
						cout << "삭제할 인덱스 번호를 입력해주십시오. >> ";
						cin >> TempString;
						cout << "삭제할 레코드는" << endl;
						NowDatabasePTR->PrintValue(TempString);
						cout << endl << "다음과 같습니다. 정말 삭제하시겠습니까?" << endl;
						cout << "삭제 원하지 않을 시 (NO) 입력 >> ";
						cin >> TempString2;
						if (!(TempString2 == "NO" || TempString2 == "no")) {
							NowDatabasePTR->DeleteValue(TempString);
						}
					}
					else if (TempString == "SORT") {
						cout << "정렬 기준으로 삼을 테이블 명을 입력해주십시오 >> ";
						cin >> TempString;
						NowDatabasePTR->STD_Sort(TempString);
					}


				}
				
			}
		}
	}
}