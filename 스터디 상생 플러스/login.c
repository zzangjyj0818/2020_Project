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
			printf("\n>>> 로그인 되었습니다 <<<\n");
			if (!(user->status))
				Programmer_window(user);
			else
				User_window(user);
		}
		else {
			system("cls");
			printf("\n!! Warning !!\n");
			printf("[비밀번호가 일치하지 않습니다]\n");
		}
	}
	else {
		system("cls");
		printf("\n!! Warning !!\n");
		printf("[아이디가 존재하지 않습니다]\n");
	}
}

User* search_Id(char Id[]) {
	for (User* p = user_head; p != NULL; p = p->next) {
		if (strcmp(p->Id, Id) == 0)
			return p;
	}
	return NULL;
}