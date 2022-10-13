#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Login.h"

User* user_head , * user_tail;
Movie* movie_head , * movie_tail;

void log_in() {
	char Id[length];
	User* user;

	printf("ID : ");
	scanf(" %s", Id);

	check_Pw(search_Id(Id));
}

void check_Pw(User* user) {
	char Pw[length];

	if (user) {
		printf("PW : ");
		scanf(" %s", Pw);

		if (!strcmp(Pw, user->Pw)) {
			system("cls");
			printf("\n>>> �α��� �Ǿ����ϴ� <<<\n");
			if (!(user->status))
				Programmer_window(user);
			else
				User_window(user);
		}
		else {
			system("cls");
			printf("\n!! Warning !!\n");
			printf("[��й�ȣ�� ��ġ���� �ʽ��ϴ�]\n");
		}
	}
	else {
		system("cls");
		printf("\n!! Warning !!\n");
		printf("[���̵� �������� �ʽ��ϴ�]\n");
	}
}

User* search_Id(char Id[]) {
	for (User* p = user_head; p != NULL; p = p->next) {
		if (strcmp(p->Id, Id) == 0)
			return p;
	}
	return NULL;
}