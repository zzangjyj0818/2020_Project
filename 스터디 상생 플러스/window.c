#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Window.h"

User* user_head, * user_tail;
Movie* movie_head, * movie_tail;
void INIT_window() {
	int menu;
	printf("\n(1) �α��� , (2) ȸ������ , (3)���̵�/��й�ȣ ã�� : ");
	scanf("%d", &menu);

	Run(menu);
}

void Run(int menu) {

    switch (menu)
    {
    case 1:
        log_in();
        break;
    case 2:
        sign_in();
        printf("\n>>> %s�� ���� �Ǿ����ϴ� <<<\n", user_tail->Id);
        Sleep(3000);
        system("cls");
        break;
    case 3:
        searching_IDPW_window();
        break;
    default:
        system("cls");
        printf("\n!! Warning !!\n");
        printf("[�߸� �������ϴ�.]\n");
        break;
    }
}

void Programmer_window(User* user) {
    int menu;
    printf("\n(1)��ȭ ���� ��� , (2)��ȭ ���� ���� , (3)��ȭ ���� ��� , (4)��ȭ ���� �˻�");
    printf("\n(5)���� ���� ���� , (6)ȸ�� ���� , (7)�α׾ƿ�");
    printf("=> "); scanf("%d", &menu);

    Programmer_Run(menu, user);
}

void User_window(User* user) {
    int menu;
    printf("\n(1)��ȭ ���� ��� , (2)��ȭ ���� �˻� , (3)��ȭ ���� , (4)���� ���� ���");
    printf("\n(5)���� ��� , (6)���� ���� ���� , (7)ȸ�� Ż�� , (8)�α׾ƿ�");
    printf("=> "); scanf("%d", &menu);

    User_Run(menu, user);
}

void Programmer_Run(int menu, User* user) {
    switch (menu)
    {
    case 1:
        insert_movie();
        system("cls");
        break;
    case 2:
        if (movie_head != NULL)
        {
            system("cls");
            delete_movie(search_title(input_title()));
        }
        else
        {
            system("cls");
            printf("\n!! Warning !!\n");
            printf("[�߸� �������ϴ�.]\n");
        }
        break;
    case 3:
        print_movie();
        break;
    case 4:
        search_movie();
        break;
    case 5:
        user_info_modification(user);
        break;
    case 6:
        user_management();
        break;
    case 7:
        printf("\n[�α׾ƿ� �Ǽ̽��ϴ�]\n");
        return;
    case 99:
        system("cls");
        break;
    default:
        system("cls");
        printf("\n!! Warning !!\n");
        printf("[�߸� �������ϴ�.]\n");
        break;
    }
    Programmer_window(user);
}

void User_Run(int menu, User* user) {
    switch (menu)
    {
    case 1:
        print_movie();
        break;
    case 2:
        search_movie();
        break;
    case 3:
        if (movie_head != NULL)
        {
            system("cls");
            reserve_movie(user);
        }
        else
        {
            system("cls");
            printf("\n!! Warning !!\n");
            printf("[�߸� �������ϴ�.]\n");
        }
        break;
    case 4:
        print_reservated_list(user);
        break;
    case 5:
        cancel_reservation(user);
        break;
    case 6:
        user_info_modification(user);
        break;
    case 7:
        user_withdrawal(user);
        return;
    case 8:
        printf("\n[�α׾ƿ� �Ǽ̽��ϴ�]\n");
        return;
    case 99:
        system("cls");
        break;
    default:
        system("cls");
        printf("\n!! Warning !!\n");
        printf("[�߸� �������ϴ�.]\n");
        break;
    }
    User_window(user);
}