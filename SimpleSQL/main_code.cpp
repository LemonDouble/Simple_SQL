#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Databases.h"
using namespace std;

int main() {
	string TempString,TempString2,TempString3,TempString4;
	// ��ɾ �Է¹��� String�� TempString ����
	string NowDatabase;
	// ���� ������� Database�� ǥ���ϱ� ���� String�� ����
	DatabaseArr Jusorok;
	// �����ͺ��̽� ��ü ����
	Database *NowDatabasePTR;
	// USE ��ɾ� ����� ���� NowDatabasePTR ������

	cout << "�ּҷ� ���α׷��Դϴ�. ��ɾ �Է��� �ֽʽÿ�." << endl << "��ɾ �� ��, HELP ��ɾ� ��� �����մϴ�. ��ɾ�� ��ҹ��ڸ� �������� �ʽ��ϴ�." << endl;

	while (1) {
		cout << ">> ";
		cin >> TempString;

		transform(TempString.begin(), TempString.end(), TempString.begin(), toupper);
		//�ҹ��ڸ� ���� ��ҹ��ڷ� �ٲ۴�. HELP, Help, help ���� HELP�� �νĵǵ��� �Ѵ�.

		if (TempString == "HELP")
			help();
		else if (TempString == "CREATE") {
			cout << "���� DATABASE ��? >>  ";
			cin >> TempString;
			Jusorok.CreateDatabase(TempString);
			cout << '<' << TempString << '>' << "  DATABASE ������" << endl;
		}
		else if (TempString == "DATABASECOUNT") {
			cout << "DATABASE ���� : " << Jusorok.DataBaseCount() << "��" << endl;
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

			cout << "����� DATABASE ��? >> ";
			cin >> TempString;

			NowDatabasePTR = Jusorok.FindDatabase(TempString);

			if (NowDatabasePTR == nullptr) {
				cout << endl << TempString << " DATABASE �˻� ����. Ȯ�� ��Ź�帳�ϴ�." << endl;
			}
			else{
				cout << endl <<TempString << "�� ����մϴ�." << endl;
				NowDatabase = TempString;
				while (1) {
					cout << NowDatabase << " >> ";
					cin >> TempString;

					transform(TempString.begin(), TempString.end(), TempString.begin(), toupper);

					if (TempString == "EXIT") {
						cout << "EXIT ��ɾ� ����. �ʱ�ȭ������ ���ư��ϴ�." << endl;
						break;
					}
					else if (TempString == "CREATETABLE") {
						cout << "���� TABLE ��? >> ";
						cin >> TempString;

						NowDatabasePTR->CreateTable(TempString);

						cout << '<' << TempString << '>' << "  TABLE ������" << endl;
					}
					else if (TempString == "DESCTABLES") {
						NowDatabasePTR->DescTables();
					}
					else if (TempString == "INPUTVALUE") {
						NowDatabasePTR->InputValue();
					}
					else if (TempString == "PRINTVALUE") {
						cout << "Print�� Record�� Index? (* �Է½� ��ü) >> ";
						cin >> TempString;
						NowDatabasePTR->PrintValue(TempString);
					}
					else if (TempString == "FINDVALUE") {
						cout << "ã�� ���̺�?(* �Է½� ��ü) >> ";
						cin >> TempString;
						cout << "ã�� ������? >> ";
						cin >> TempString2;
						if(!(NowDatabasePTR->FindValue(TempString, TempString2))){
							cout << "�����͸� ã�� �� �������ϴ�." << endl;
						}
					}
					else if (TempString == "CHANGEVALUE") {
						cout << "������ �����Ͱ� �ִ� ���̺�? >> ";
						cin >> TempString;
						cout << "������ �����Ͱ� �ִ� �ε���? >> ";
						cin >> TempString2;
						TempString4 = NowDatabasePTR->FindChangeData(TempString, TempString2);

						if (TempString4 != "ERROR") {
							cout << "������ �����ʹ� { " << TempString4 << " } ���Դϴ�." << endl;
							cout << "�ٲ� �����͸� �Է��� �ֽʽÿ�. (���� ������ ���� �� NO �Է�) >> ";
							cin >> TempString3;
							if (!(TempString3 == "NO" || TempString3 == "no")) {
								NowDatabasePTR->ChangeValue(TempString, TempString2, TempString3);
							}
						}
					}
					else if (TempString == "DELETEVALUE") {
						cout << "������ �ε��� ��ȣ�� �Է����ֽʽÿ�. >> ";
						cin >> TempString;
						cout << "������ ���ڵ��" << endl;
						NowDatabasePTR->PrintValue(TempString);
						cout << endl << "������ �����ϴ�. ���� �����Ͻðڽ��ϱ�?" << endl;
						cout << "���� ������ ���� �� (NO) �Է� >> ";
						cin >> TempString2;
						if (!(TempString2 == "NO" || TempString2 == "no")) {
							NowDatabasePTR->DeleteValue(TempString);
						}
					}
					else if (TempString == "SORT") {
						cout << "���� �������� ���� ���̺� ���� �Է����ֽʽÿ� >> ";
						cin >> TempString;
						NowDatabasePTR->STD_Sort(TempString);
					}


				}
				
			}
		}
	}
}