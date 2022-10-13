#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>

#include "User_func.h"

User* user_head, * user_tail;
Movie* movie_head, * movie_tail;

void user_withdrawal(User* user) //회원 탈퇴
{
	for (Movie* movie = movie_head; movie != NULL; movie = movie->next) //사용자가 Movie DB에 남긴 흔적 초기화
	{
		for (int i = 0; i < 16; i++)
		{
			if (strcmp(movie->size.Reserved_id[i], user->Id) == 0) //흔적이 있는 경우
			{
				(movie->reservated)--; //1 감소
				sprintf(movie->size.Reserved_id[i], "%d", i + 1); //다시 좌석 번호로 수정
				movie->size.seat[i] = 0; //1 -> 0 
			}
		}
	}

	if (user == user_head)
	{
		user_head = user->next;
	}
	else if (user == user_tail)
	{
		User* pre = search_pre_user(user);
		user_tail = pre;
		pre->next = NULL;
	}
	else
	{
		User* pre = search_pre_user(user);
		pre->next = user->next;
	}
	free(user);

	printf("\n>>> 회원 탈퇴 성공 <<<\n");
}

void reserve_movie(User* user)
{
	int menu;
	printf("\n==========영화 목록==========\n");
	do {
		printf("\n(1)예매하기 , (2)돌아가기 : ");
		scanf("%d", &menu);
		if (menu == 2)
			return;
		if (menu != 1)
			printf("\n다시 입력하세요\n");
	} while (menu != 1);

	Movie* movie = reserve_number(); // -> 영화 리스트에서 번호로 영화 예매할 수 있도록 <- //

	if (movie)
	{
		if (movie->reservated == 16)
		{
			printf("\n>>> Full seat <<<\n");
			return;
		}
		Reservation* tmp = (Reservation*)malloc(sizeof(Reservation) * (++(user->reservation)));
		if (user->reservation == 1) //예매한 영화가 1개인 경우
		{
			strcpy(tmp->Title, movie->Title);
			tmp->year = movie->year;
			strcpy(tmp->Company, movie->Company);
		}
		else
		{
			for (int i = 0; i < user->reservation-1; i++)
			{
				if (strcmp(movie->Title, ((user->List) + i)->Title) == 0)
				{
					printf("\n>>> 중복 예매 불가 <<<\n");
					(user->reservation)--;
					return;
				}
			}

			for (int i = 1; i < user->reservation; i++)
			{
				strcpy((tmp + i)->Title, ((user->List) + i - 1)->Title);
				(tmp + i)->year = ((user->List) + i - 1)->year;
				strcpy((tmp + i)->Company, ((user->List) + i - 1)->Company);
			}

			strcpy(tmp->Title, movie->Title);
			tmp->year = movie->year;
			strcpy(tmp->Company, movie->Company);
		}
		(movie->reservated)++; //영화의 총 예매된 수 1 증가
		seat_reservation(movie, user);
		user->List = tmp;
		printf("\n-> %s가 예매되었습니다.\n", movie->Title);
	}
	else
		printf("\n>>> 일치하는 영화가 없습니다 <<<\n");
}

// -> 번호를 보고 예매할 수 있도록 다시 구현 <- //
Movie*	reserve_number()
{
	int num; // 변호랑 비교할 변수 선언
	int cnt = 1; // 비교 변수 선언

	int i = 1; // 영화 번호인 정수형 변수 선언

	for (Movie* p = movie_head; p != NULL; p = p->next) // 구조체 연결리스트 처음부터 끝까지 반복
	{
		printf("\n====================\n");
		printf("Number:    %d\n", i);
		printf("Title :    %s\n", p->Title);
		printf("Year  :    %d\n", p->year);
		printf("Company :  %s\n", p->Company);

		i++;
	}

	printf("\n몇번 영화로 예매하겠습니까?\n");
	scanf("%d", &num);

	for (Movie* p = movie_head; p != NULL; p = p->next) // 영화의 첫 부분부터 마지막까지 반복
	{
		if (cnt == num)
		{
			return p;
		}
		cnt++;
	}
	return NULL;
}
void seat_reservation(Movie* movie, User* user)
{
	int seat_number; //예매할 좌석의 번호
	system("cls");   //화면 초기화
	printf("\n[좌석을 선택하세요]\n");
	for (int i = 0; i < 16; i++) //총 좌석 수는 16자리로 고정
	{
		printf("%d(%s)", movie->size.seat[i], movie->size.Reserved_id[i]);
		//좌석의 예매 유무와 예매 아이디 출력(만약 예매되지 않았으면 좌석의 번호 출력
		for (int k = 0; k < 20 - strlen(movie->size.Reserved_id[i]); k++)
			printf(" ");   //자리수를 맞추기 위해 아이디만큼의 띄어쓰기를 지움
		if (i % 4 == 3)
			printf("\n\n");
	}
	printf("┌------------------------------------------------------------------------┐\n");
	printf("│                               [  Screen  ]                             │\n");
	printf("└------------------------------------------------------------------------┘\n");
	while (1)
	{
		printf(">>>");
		scanf("%d", &seat_number);
		if (seat_number >= 1 && seat_number <= 16)
		{
			if (movie->size.seat[seat_number - 1] == 1)
				printf(">>> %d 좌석은 예매 되어있습니다 <<<", seat_number);
			else      //좌석이 예매되어 있지 않다면
			{
				movie->size.seat[seat_number - 1] = 1;
				strcpy(movie->size.Reserved_id[seat_number - 1], user->Id);
				system("cls");
				for (int i = 0; i < 16; i++) //총 좌석 수는 16자리로 고정
				{
					printf("%d(%s)", movie->size.seat[i], movie->size.Reserved_id[i]);
					//위에서 등록한 자리의 정보를 저장하여 출력
					for (int k = 0; k < 20 - strlen(movie->size.Reserved_id[i]); k++)
						printf(" ");   //자리수를 맞추기 위해 아이디만큼의 띄어쓰기를 지움
					if (i % 4 == 3)         //한 줄에 4 개씩 출력
						printf("\n\n");
				}
				printf("┌------------------------------------------------------------------------┐\n");
				printf("│                               [  Screen  ]                             │\n");
				printf("└------------------------------------------------------------------------┘\n");
				printf("-> %d 좌석이 예매되었습니다.", seat_number);
				break;
			}
		}
		else      //만약 1~16의 숫자를 입력하지 않았다면
			printf("\n>>> 다시 입력하세요 <<<\n");
	}
}

void print_reservated_list(User* user)
{
	if (user->List == NULL)
		printf("\n>>> 예매한 영화가 없습니다 <<<\n");
	else
	{
		for (int i = 0; i < user->reservation; i++)
		{
			printf("\n#%d번째 영화\n", user->reservation - i);

			printf("영화 제목   :  %s\t", ((user->List) + i)->Title);
			printf("개봉 연도   :  %d\t", ((user->List) + i)->year);
			printf("영화 배급사 :  %s\t", ((user->List) + i)->Company);

			printf("\n");
		}
	}
}

void cancel_reservation(User* user)
{
	int len = (user->reservation); //예매한 영화의 수

	print_reservated_list(user);
	if (len < 1) //예매 내역이 없는 경우
		return;

	int num;

	do {
		printf("\n취소할 영화 번호 => ");
		scanf("%d", &num);
	} while (num > len || num < 1); //영화 번호를 잘못 입력한 경우

	Movie* movie = NULL;
	Reservation* tmp = (Reservation*)malloc(sizeof(Reservation) * (len - 1));
	int index = 0; //tmp의 인덱스 값 저장
	for (int i = 0; i < len; i++)
	{
		if (num != i + 1)
		{
			memcpy(tmp + index, (user->List) + i, sizeof(Reservation));
		}
		else
		{
			printf("\n>>> %s 영화가 예매 취소되었습니다 <<<\n", ((user->List) + i)->Title);
			movie = search_title(((user->List) + i)->Title); //해당 영화를 찾아서 할당
		}
	}
	if (movie)
	{
		(user->reservation)--; //영화 예매 수 1 감소
		user->List = tmp;

		//-> 영화 스크린에서도 제외 <- //
		(movie->reservated)--; //전체 영화 관람자 수 감소
		for (int i = 0; i < 16; i++)
		{
			if (strcmp(user->Id, movie->size.Reserved_id[i]) == 0) //해당 사용자의 좌석 초기화
			{
				sprintf(movie->size.Reserved_id[i], "%d", i + 1); //integer to string
				movie->size.seat[i] = 0;
			}
		}
	}
}