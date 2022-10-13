#pragma once
#define length 20

typedef struct Resevation {
	char Title[length], Company[length]; //영화 제목
	int year; //개봉 연도
} Reservation;

typedef struct User {
	char Id[length], Pw[length]; //아이디, 비밀번호
	char Phone[length], name[length]; //전화번호, 이름
	int age, status; //나이, 신분
	int reservation; //예매 수
	struct User* next; //User 필드의 다음을 가리킬 포인터
	Reservation* List; //영화 예매 내역
} User;