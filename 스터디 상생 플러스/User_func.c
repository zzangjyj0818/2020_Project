#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>

#include "User_func.h"

User* user_head, * user_tail;
Movie* movie_head, * movie_tail;

void user_withdrawal(User* user) //ȸ�� Ż��
{
	for (Movie* movie = movie_head; movie != NULL; movie = movie->next) //����ڰ� Movie DB�� ���� ���� �ʱ�ȭ
	{
		for (int i = 0; i < 16; i++)
		{
			if (strcmp(movie->size.Reserved_id[i], user->Id) == 0) //������ �ִ� ���
			{
				(movie->reservated)--; //1 ����
				sprintf(movie->size.Reserved_id[i], "%d", i + 1); //�ٽ� �¼� ��ȣ�� ����
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

	printf("\n>>> ȸ�� Ż�� ���� <<<\n");
}

void reserve_movie(User* user)
{
	int menu;
	printf("\n==========��ȭ ���==========\n");
	do {
		printf("\n(1)�����ϱ� , (2)���ư��� : ");
		scanf("%d", &menu);
		if (menu == 2)
			return;
		if (menu != 1)
			printf("\n�ٽ� �Է��ϼ���\n");
	} while (menu != 1);

	Movie* movie = reserve_number(); // -> ��ȭ ����Ʈ���� ��ȣ�� ��ȭ ������ �� �ֵ��� <- //

	if (movie)
	{
		if (movie->reservated == 16)
		{
			printf("\n>>> Full seat <<<\n");
			return;
		}
		Reservation* tmp = (Reservation*)malloc(sizeof(Reservation) * (++(user->reservation)));
		if (user->reservation == 1) //������ ��ȭ�� 1���� ���
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
					printf("\n>>> �ߺ� ���� �Ұ� <<<\n");
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
		(movie->reservated)++; //��ȭ�� �� ���ŵ� �� 1 ����
		seat_reservation(movie, user);
		user->List = tmp;
		printf("\n-> %s�� ���ŵǾ����ϴ�.\n", movie->Title);
	}
	else
		printf("\n>>> ��ġ�ϴ� ��ȭ�� �����ϴ� <<<\n");
}

// -> ��ȣ�� ���� ������ �� �ֵ��� �ٽ� ���� <- //
Movie*	reserve_number()
{
	int num; // ��ȣ�� ���� ���� ����
	int cnt = 1; // �� ���� ����

	int i = 1; // ��ȭ ��ȣ�� ������ ���� ����

	for (Movie* p = movie_head; p != NULL; p = p->next) // ����ü ���Ḯ��Ʈ ó������ ������ �ݺ�
	{
		printf("\n====================\n");
		printf("Number:    %d\n", i);
		printf("Title :    %s\n", p->Title);
		printf("Year  :    %d\n", p->year);
		printf("Company :  %s\n", p->Company);

		i++;
	}

	printf("\n��� ��ȭ�� �����ϰڽ��ϱ�?\n");
	scanf("%d", &num);

	for (Movie* p = movie_head; p != NULL; p = p->next) // ��ȭ�� ù �κк��� ���������� �ݺ�
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
	int seat_number; //������ �¼��� ��ȣ
	system("cls");   //ȭ�� �ʱ�ȭ
	printf("\n[�¼��� �����ϼ���]\n");
	for (int i = 0; i < 16; i++) //�� �¼� ���� 16�ڸ��� ����
	{
		printf("%d(%s)", movie->size.seat[i], movie->size.Reserved_id[i]);
		//�¼��� ���� ������ ���� ���̵� ���(���� ���ŵ��� �ʾ����� �¼��� ��ȣ ���
		for (int k = 0; k < 20 - strlen(movie->size.Reserved_id[i]); k++)
			printf(" ");   //�ڸ����� ���߱� ���� ���̵�ŭ�� ���⸦ ����
		if (i % 4 == 3)
			printf("\n\n");
	}
	printf("��------------------------------------------------------------------------��\n");
	printf("��                               [  Screen  ]                             ��\n");
	printf("��------------------------------------------------------------------------��\n");
	while (1)
	{
		printf(">>>");
		scanf("%d", &seat_number);
		if (seat_number >= 1 && seat_number <= 16)
		{
			if (movie->size.seat[seat_number - 1] == 1)
				printf(">>> %d �¼��� ���� �Ǿ��ֽ��ϴ� <<<", seat_number);
			else      //�¼��� ���ŵǾ� ���� �ʴٸ�
			{
				movie->size.seat[seat_number - 1] = 1;
				strcpy(movie->size.Reserved_id[seat_number - 1], user->Id);
				system("cls");
				for (int i = 0; i < 16; i++) //�� �¼� ���� 16�ڸ��� ����
				{
					printf("%d(%s)", movie->size.seat[i], movie->size.Reserved_id[i]);
					//������ ����� �ڸ��� ������ �����Ͽ� ���
					for (int k = 0; k < 20 - strlen(movie->size.Reserved_id[i]); k++)
						printf(" ");   //�ڸ����� ���߱� ���� ���̵�ŭ�� ���⸦ ����
					if (i % 4 == 3)         //�� �ٿ� 4 ���� ���
						printf("\n\n");
				}
				printf("��------------------------------------------------------------------------��\n");
				printf("��                               [  Screen  ]                             ��\n");
				printf("��------------------------------------------------------------------------��\n");
				printf("-> %d �¼��� ���ŵǾ����ϴ�.", seat_number);
				break;
			}
		}
		else      //���� 1~16�� ���ڸ� �Է����� �ʾҴٸ�
			printf("\n>>> �ٽ� �Է��ϼ��� <<<\n");
	}
}

void print_reservated_list(User* user)
{
	if (user->List == NULL)
		printf("\n>>> ������ ��ȭ�� �����ϴ� <<<\n");
	else
	{
		for (int i = 0; i < user->reservation; i++)
		{
			printf("\n#%d��° ��ȭ\n", user->reservation - i);

			printf("��ȭ ����   :  %s\t", ((user->List) + i)->Title);
			printf("���� ����   :  %d\t", ((user->List) + i)->year);
			printf("��ȭ ��޻� :  %s\t", ((user->List) + i)->Company);

			printf("\n");
		}
	}
}

void cancel_reservation(User* user)
{
	int len = (user->reservation); //������ ��ȭ�� ��

	print_reservated_list(user);
	if (len < 1) //���� ������ ���� ���
		return;

	int num;

	do {
		printf("\n����� ��ȭ ��ȣ => ");
		scanf("%d", &num);
	} while (num > len || num < 1); //��ȭ ��ȣ�� �߸� �Է��� ���

	Movie* movie = NULL;
	Reservation* tmp = (Reservation*)malloc(sizeof(Reservation) * (len - 1));
	int index = 0; //tmp�� �ε��� �� ����
	for (int i = 0; i < len; i++)
	{
		if (num != i + 1)
		{
			memcpy(tmp + index, (user->List) + i, sizeof(Reservation));
		}
		else
		{
			printf("\n>>> %s ��ȭ�� ���� ��ҵǾ����ϴ� <<<\n", ((user->List) + i)->Title);
			movie = search_title(((user->List) + i)->Title); //�ش� ��ȭ�� ã�Ƽ� �Ҵ�
		}
	}
	if (movie)
	{
		(user->reservation)--; //��ȭ ���� �� 1 ����
		user->List = tmp;

		//-> ��ȭ ��ũ�������� ���� <- //
		(movie->reservated)--; //��ü ��ȭ ������ �� ����
		for (int i = 0; i < 16; i++)
		{
			if (strcmp(user->Id, movie->size.Reserved_id[i]) == 0) //�ش� ������� �¼� �ʱ�ȭ
			{
				sprintf(movie->size.Reserved_id[i], "%d", i + 1); //integer to string
				movie->size.seat[i] = 0;
			}
		}
	}
}