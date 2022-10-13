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
	user->reservation = 0; // ���� �� 0���� �ʱ�ȭ
	user->List = NULL;

	while (1) {
		printf("ID�Է�: ");
		scanf(" %s", Id);

		if (compare_duplication(Id) == 0) {
			system("cls");
			printf("\n!! Warning !!\n");
			printf("[�ߺ��Ǿ����ϴ�]\n");
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

	printf("�̸� �Է�: ");
	scanf(" %s", user->name);
	printf("��ȭ��ȣ �Է�: ");
	scanf(" %s", user->Phone);
	printf("���� �Է�: ");
	scanf("%d", &user->age);

	bot_check();

	do
	{
		printf("(0)������ , (1)����� : ");
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
		printf("PW �Է� : ");
		scanf(" %s", cmp_Pw);
		
		if (check_IdPw_length(cmp_Pw) == 0 || check_eng_digit(cmp_Pw) == 0)
			continue;
		else
			break;
	}

	while (1) {
		printf("PW Ȯ�� : ");
		scanf(" %s", Pw);
		if (strcmp(Pw, cmp_Pw) == 0)
			break;
		else {
			printf("\n!! Warning !!\n");
			printf("[��й�ȣ�� ��ġ���� �ʽ��ϴ�.]\n");
		}
	}
}

int check_IdPw_length(char* user) {
	int len = strlen(user);
	
	if (len > 10) {
		printf("\n[10���� ���Ϸ� �ٽ� �Է��ϼ���.]\n");

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

	printf("\n[ID/PW�� �����ڿ� ���ڷθ� �̷�������մϴ�.]\n");

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
		printf("�ڵ� ���� ���� �ڵ� (%s)", arr);
		scanf(" %s", user_arr);


		if (!strcmp(arr, user_arr))
			break;
		else
			printf("[�ٽ� �Է��ϼ���.]");
	}
}