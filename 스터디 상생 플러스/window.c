#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Window.h"

User* user_head, * user_tail;
Movie* movie_head, * movie_tail;
void INIT_window() {
	int menu;
	printf("\n(1) 로그인 , (2) 회원가입 , (3)아이디/비밀번호 찾기 : ");
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
        printf("\n>>> %s님 가입 되었습니다 <<<\n", user_tail->Id);
        Sleep(3000);
        system("cls");
        break;
    case 3:
        searching_IDPW_window();
        break;
    default:
        system("cls");
        printf("\n!! Warning !!\n");
        printf("[잘못 눌렀습니다.]\n");
        break;
    }
}

void Programmer_window(User* user) {
    int menu;
    printf("\n(1)영화 정보 등록 , (2)영화 정보 삭제 , (3)영화 정보 출력 , (4)영화 정보 검색");
    printf("\n(5)개인 정보 수정 , (6)회원 관리 , (7)로그아웃");
    printf("=> "); scanf("%d", &menu);

    Programmer_Run(menu, user);
}

void User_window(User* user) {
    int menu;
    printf("\n(1)영화 정보 출력 , (2)영화 정보 검색 , (3)영화 예매 , (4)예매 내역 출력");
    printf("\n(5)예매 취소 , (6)개인 정보 수정 , (7)회원 탈퇴 , (8)로그아웃");
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
            printf("[잘못 눌렀습니다.]\n");
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
        printf("\n[로그아웃 되셨습니다]\n");
        return;
    case 99:
        system("cls");
        break;
    default:
        system("cls");
        printf("\n!! Warning !!\n");
        printf("[잘못 눌렀습니다.]\n");
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
            printf("[잘못 눌렀습니다.]\n");
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
        printf("\n[로그아웃 되셨습니다]\n");
        return;
    case 99:
        system("cls");
        break;
    default:
        system("cls");
        printf("\n!! Warning !!\n");
        printf("[잘못 눌렀습니다.]\n");
        break;
    }
    User_window(user);
}