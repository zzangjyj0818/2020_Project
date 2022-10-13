#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "Signin.h"

User* user_head, * user_tail;
Movie* movie_head, * movie_tail;

void sign_in() {
	if (user_head != NULL) {
		user_tail->next = (User*)malloc(sizeof(User));
		user_tail = user_tail->next;
	}

	else{
		user_head = (User*)malloc(sizeof(User));
		user_tail = user_head;
	}

	input_user_info(user_tail);

	user_tail->next = NULL;
}

void input_user_info(User* user) {
	printf("\n========================\n");
	char* Id = (char*)malloc(sizeof(char) * 20);
	user->reservation = 0; // 예매 수 0으로 초기화
	user->List = NULL;

	while (1) {
		printf("ID입력: ");
		scanf(" %s", Id);

		if (compare_duplication(Id) == 0) {
			system("cls");
			printf("\n!! Warning !!\n");
			printf("[중복되었습니다]\n");
			continue;
		}

		else {
			if (check_IdPw_length(Id) == 0 || check_eng_digit(Id) == 0)
				continue;
			else
				break;
		}
	}

	strcpy(user->Id, Id);
	Pw_cmp(user->Pw);

	printf("이름 입력: ");
	scanf(" %s", user->name);
	printf("전화번호 입력: ");
	scanf(" %s", user->Phone);
	printf("나이 입력: ");
	scanf("%d", &user->age);

	bot_check();

	do
	{
		printf("(0)관리자 , (1)사용자 : ");
		scanf("%d", &user->status);
	} while (user->status != 0 && user->status != 1);
}

int compare_duplication(char* Id) {
	if (user_head == NULL || user_head == user_tail)
		return 1;
	else {
		for (User* p = user_head; p != user_tail; p = p->next) {
			if (!strcmp(p->Id, Id))
			{
				return 0;
			}
		}
	}
	return 1;
}

void Pw_cmp(char Pw[]) {
	char cmp_Pw[length];

	while (1) {
		printf("PW 입력 : ");
		scanf(" %s", cmp_Pw);
		
		if (check_IdPw_length(cmp_Pw) == 0 || check_eng_digit(cmp_Pw) == 0)
			continue;
		else
			break;
	}

	while (1) {
		printf("PW 확인 : ");
		scanf(" %s", Pw);
		if (strcmp(Pw, cmp_Pw) == 0)
			break;
		else {
			printf("\n!! Warning !!\n");
			printf("[비밀번호가 일치하지 않습니다.]\n");
		}
	}
}

int check_IdPw_length(char* user) {
	int len = strlen(user);
	
	if (len > 10) {
		printf("\n[10글자 이하로 다시 입력하세요.]\n");

		return 0;
	}

	return 1;
}

int check_eng_digit(char* user) {
	int len = strlen(user);
	int cnt = 0;

	for (int i = 0; i < len; i++) {
		if (isalpha(user[i]))
			cnt++;
		else if (isdigit(user[i]))
			cnt++;
	}

	if (cnt == len)
		return 1;

	printf("\n[ID/PW는 영문자와 숫자로만 이루어져야합니다.]\n");

	return 0;
}

void bot_check() {
	char user_arr[6];
	char arr[6];
	int r;
	srand(time(NULL));
	while (1) {
		for (int i = 0; i < 5; i++) {
			r = rand() % 2;
			if (!r)
				arr[i] = rand() % 9 + 48;
			else
				arr[i] = rand() % 26 + 65;
		}

		arr[5] = '\0';
		printf("자동 가입 방지 코드 (%s)", arr);
		scanf(" %s", user_arr);


		if (!strcmp(arr, user_arr))
			break;
		else
			printf("[다시 입력하세요.]");
	}
}