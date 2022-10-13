#pragma once
#define SIZE 16
#define length 20

typedef struct Hall {
	int seat[SIZE]; //좌석 수
	char Reserved_id[SIZE][length]; //예약된 아이디의 좌석
} Hall;

typedef struct Movie {
	char Title[length], Company[length]; //영화 제목 , 배급사
	int year, reservated; //개봉연도 , 예매 수
	Hall size; //영화관의 정보 (크기, 예약 아이디)
	struct Movie* next; //Movie 필드의 다음을 가리킬 포인터
} Movie;