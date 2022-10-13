#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>

#include "Function.h"

User* user_head, * user_tail;
Movie* movie_head, * movie_tail;

char* input_title()
{
    char* title = (char*)malloc(sizeof(char) * 20);
    printf("검색할 제목: ");
    scanf(" %[^\n]", title);

    return title;
}

char* delete_space(char* string)
{
    char* changed;
    changed = (char*)malloc(sizeof(char) * 20);
    int cnt = 0;

    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] != ' ')
            changed[cnt++] = string[i];
    }
    changed[cnt] = '\0'; //Last string is always null
    return changed;
}

// movie search // for both
Movie* search_title(char* title)
{
    for (Movie* p = movie_head; p != NULL; p = p->next)
    {

        if (strcmp(delete_space(title), delete_space(p->Title)) == 0)
            return p;
    }
    return NULL;
}

// etc. activity //
void search_movie()
{
    if (movie_head == NULL)
    {
        printf("\n[등록된 영화가 없습니다.]\n");
        return;
    }

    Movie* p;
    p = search_title(input_title());

    if (p)
    {
        printf("\n=======================\n");

        printf("\n제목: %s\n", p->Title);
        printf("\n개봉연도: %d\n", p->year);
        printf("\n배급사: %s\n", p->Company);
        printf("\n예매 수: %d ( %d / 16 )\n", p->reservated, 16 - p->reservated);

        printf("\n=======================\n");
    }
    else
        printf("\n[찾으시는 영화가 없습니다.]\n");
}

// movie print // for both
void print_movie()
{
    int cnt = 0, flag[5];

    if (movie_head == NULL)
    {
        printf("\n[등록된 영화가 없습니다.]\n");
        return;
    }

    Movie* tmp, * start;
    start = movie_head;
    for (int i = 0; i < 5; i++)
        flag[i] = 0;
    for (Movie* p = start; p != NULL; p = p->next)
    {
        cnt++;
    }
    while (1)
    {
        for (int i = flag[0]; i < cnt; i++)
        {
            printf("#%d\t\t\t\t", i + 1);
            flag[0]++;
            if (flag[0] % 4 == 0)
            {
                break;
            }
        }
        printf("\n");
        for (Movie* p = start; p != NULL; p = p->next)
        {
            printf("영화 제목: %s\t\t\t", p->Title);
            flag[1]++;
            if (flag[1] % 4 == 0)
            {
                break;
            }
        }
        printf("\n");
        for (Movie* p = start; p != NULL; p = p->next)
        {
            printf("개봉 연도: %d\t\t\t", p->year);
            flag[2]++;
            if (flag[2] % 4 == 0)
            {
                break;
            }
        }
        printf("\n");
        for (Movie* p = start; p != NULL; p = p->next)
        {
            printf("배급사: %s\t\t\t", p->Company);
            flag[3]++;
            if (flag[3] % 4 == 0)
            {
                break;
            }
        }
        printf("\n");
        for (Movie* p = start; p != NULL; p = p->next)
        {
            printf("예매 수: %d/16\t\t\t", p->reservated);
            flag[4]++;
            if (flag[4] % 4 == 0)
            {
                tmp = p->next;
                start = tmp;
                break;
            }
        }
        if (flag[0] == cnt)
            break;
    }
    printf("\n");
    start = movie_head;
    cnt = 0;

    return;
}

//개인정보 수정
void user_info_modification(User* p)
{
    char Pw[length], New_pw[length];
    int cnt = 0;
    char tmp[length];
    strcpy(tmp, (p)->Pw);
    while (1)
    {
        printf("\n원래 PW: ");
        scanf(" %s", Pw);

        if (!strcmp(tmp, Pw))
            break;
        else
        {
            system("cls");
            if (cnt == 2) //총 3회
                return;
            printf("\n입력한 PW가 기존의 PW와 다릅니다. 다시 입력하세요.\n");
            printf("\n3회 이상 틀릴 시 초기화면으로 되돌아 갑니다.\n");
            cnt++;
        }
    }

    while (1)
    {
        do
        {
            printf("\n변경할 PW 입력: ");
            scanf(" %s", New_pw);
        } while (check_IdPw_length(New_pw) != 1 && check_eng_digit(New_pw) != 1);

        if (strcmp(New_pw, tmp) == 0)
        {
            printf("입력한 PW가 기존의 PW와 같습니다. 다시 입력하세요.\n");
        }

        else
            break;
    }

    strcpy((p)->Pw, New_pw);

    printf("\n변경된 PW 확인: %s", (p)->Pw);

    return;
}

void searching_IDPW_window()
{
    int choice;
    if (user_head == NULL)
    {
        printf("회원 DB가 없습니다.\n");
        return;
    }
    printf("(1) ID 찾기  (2) PW 찾기 (3) 돌아가기 : ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        searching_ID();
        break;
    case 2:
        searching_PW();
        break;
    case 3:
        break;
    default:
        printf("잘못 누르셨습니다.\n");
        break;
    }
    return;
}
void searching_ID()
{
    int flag = 0;
    char input_p[20], input_n[20]; //배열을 새로 만들고

    printf("\n전화번호와 이름을 입력하세요.\n");
    printf("전화번호 : ");
    scanf("%s", input_p);
    printf("이름 : ");
    scanf("%s", input_n);
    for (User* p = user_head; p != NULL; p = p->next)
    {
        if ((strcmp(input_p, p->Phone) == 0) && (strcmp(input_n, p->name) == 0))
        {
            printf("\n[아이디 : %s]\n", p->Id);
            flag = 1;
            for (int i = 3; i > 0; i--)
            {
                Sleep(1500);
                printf("%d초후에 사라집니다.\n", i);
            }
            system("cls");
            break;
        }
    }
    if (flag == 0)
    {
        printf("입력하신 정보가 틀리셨습니다.\n");
    }

    flag = 0;
    return;
}

void searching_PW()
{
    int flag = 0;
    char input_p[20], input_n[20], input_ID[20]; //배열을 새로 만들고

    printf("\n아이디,전화번호와 이름을 입력하세요.\n");
    printf("ID : ");
    scanf("%s", input_ID);
    printf("전화번호 : ");
    scanf("%s", input_p);
    printf("이름 : ");
    scanf("%s", input_n);
    for (User* p = user_head; p != NULL; p = p->next)
    {
        if ((strcmp(input_p, p->Phone) == 0) && (strcmp(input_n, p->name) == 0) && (strcmp(input_ID, p->Id) == 0))
        {
            printf("[비밀번호 : ");
            for (int i = 0; i < strlen(p->Pw); i++)
            {
                if (strlen(p->Pw) / 2 > i)
                    printf("%c", p->Pw[i]);
                else
                    printf("*");
            }
            printf("]\n");
            for (int i = 3; i > 0; i--)
            {
                Sleep(1500);
                printf("%d초후에 사라집니다.\n", i);
            }
            system("cls");
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("입력하신 정보가 틀리셨습니다.\n");
    }
    flag = 0;
}