#Smple_SQL

C++과 STL을 공부하면서 배운 지식을 이용하여, Mysql의 기본적인 기능을 구현해 본 프로그램입니다.

명령어는 다음과 같으며, 대소문자를 구분하지 않습니다.

프로그램 실행은 SimpleSQL.sln을 visual studio 로 실행하여 사용하며, 개발 당시에는 VS2015 버전을 사용했습니다.

사용 가능한 명령어는 다음과 같습니다.

```
HELP -> 도움말을 출력합니다. (아래 모든 커맨드를 출력합니다)
CREATE <DATABASE 명> -> DATABASE 명에 맞는 데이터베이스를 만듭니다.
DATABASECOUNT -> DATABASE의 개수를 출력합니다.
DESCDATABASES -> DATABASE명을 전부 출력합니다
USE <DATABASE 명> -> DATABASE명에 맞는 데이터베이스를 사용합니다.
(USE 사용 후) EXIT -> 데이터베이스 사용을 종료하고 초기 화면으로 돌아갑니다.
(USE 사용 후) CREATETABLE <TABLE 명> -> TABLE 명에 맞는 테이블을 출력합니다.
(USE 사용 후) DESCTABLES -> 현 DATABASE에 있는 TABLE명을 전부 출력합니다.
(USE 사용 후) INPUTVALUE -> RECORD 한 줄을 입력합니다.
(USE 사용 후) PRINTVALUE <출력할 데이터의 INDEX> -> 해당 인덱스를 가지고 있는 레코드를 출력합니다.
(USE 사용 후) FINDVALUE  <찾을 테이블 명> <찾을 데이터> -> 해당 테이블에서 해당 데이터와 일치하는 레코드의 인덱스를 전부 출력합니다.
(USE 사용 후) CHANGEVALUE <수정할 데이터가 있는 TABLE 명> <수정할 데이터가 있는 INDEX> -> TABLE명과 INDEX가 일치하는 곳 에 있는 데이터를 수정합니다.
(USE 사용 후) DELETEVALUE <삭제할 인덱스 번호> -> INDEX와 일치하는 레코드를 삭제합니다.
(USE 사용 후) SORT <기준이 될 테이블 명> -> 그 테이블을 기준으로 데이터를 정렬합니다.
```