#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>

#include "Programmer_func.h"

User* user_head, * user_tail;
Movie* movie_head, * movie_tail;

//insert movie information
void movie_information(Movie* movie)
{
    printf("\n=======================\n");

    while (1)
    {
        printf("영화 제목 : ");
        scanf(" %[^\n]", movie->Title);

        if ((movie_title_compare(movie->Title)))
            break;
        else
            printf("이미 등록된 영화입니다\n");
    }
    printf("개봉 연도 : ");
    scanf("%d", &movie->year);
    printf("배급사: ");
    scanf(" %[^\n]", movie->Company);

    printf("\n=======================\n");

    char arr[16][3] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16" };

    for (int i = 0; i < 16; i++)
    {
        movie->size.seat[i] = 0;
        strcpy(movie->size.Reserved_id[i], arr[i]);
    }
    printf("<%s>가 등록되었습니다.\n", movie->Title);
    for (int i = 0; i < 2; i++)
        Sleep(1000);
    system("cls");
}

int movie_title_compare(char* title)
{
    for (Movie* p = movie_head; p != movie_tail; p = p->next) //movie_tail = 입력받고 있는 공간
    {
        if (strcmp(delete_space(p->Title), delete_space(title)) == 0)
            return 0;
    }

    return 1;
}

// movie insert // for programmer
void insert_movie()
{
    if (movie_head != NULL)
    {
        movie_tail->next = (Movie*)malloc(sizeof(Movie));
        movie_tail = movie_tail->next;
    }
    else
    {
        movie_head = (Movie*)malloc(sizeof(Movie));
        movie_tail = movie_head;
    }

    movie_information(movie_tail);
    movie_tail->reservated = 0;
    movie_tail->next = NULL;
}

Movie* search_pre_node(Movie* p)
{
    Movie* pre;
    for (pre = movie_head; pre->next != p; pre = pre->next)
    {

    }
    return pre;
}

// movie delete // for programmer
void delete_movie(Movie* p)
{
    if (p == NULL)
    {
        printf("\n[영화 DB에 데이터가 없습니다.]\n");
        return;
    }

    ////////////////////////////////////////////////
    if (p == movie_head)
    {
        movie_head = p->next;
        free(p);
    }
    else if (p == movie_tail)
    {
        Movie* pre = search_pre_node(p);
        movie_tail = pre; /// !
        pre->next = NULL;
        free(p);
    }
    else // p == movie_middle
    {
        Movie* pre = search_pre_node(p);
        pre->next = p->next;
        free(p);
    }
    ////////////////////////////////////////////////
    printf("\n[성공적으로 삭제되었습니다.]\n");
}

void user_management()
{
    int num;
    printf("\n(1)회원 리스트 출력 (2)회원 삭제");
    printf("\n==>");
    scanf("%d", &num);

    switch (num)
    {
    case 1:
        print_user_list();
        break;
    case 2:
        delete_user();
        break;
    default:
        printf("\n[잘못 눌렀습니다.]\n");
        break;
    }
    return;
}

User* search_pre_user(User* p)
{
    User* pre;
    for (pre = user_head; pre->next != p; pre = pre->next)
    {
        //pre->next = p
    }
    return pre;  //pre = p전의 구조체
}
// user print // for programmer
void print_user_list()
{
    int num, flag;
    if (user_head == NULL)
    {
        printf("\n[등록된 회원이 없습니다.]\n");
        return;
    }

    printf("(1)전체 출력  (2)사용자 출력  (3)관리자 출력");
    printf("\n==>");
    scanf("%d", &num);

    switch (num)
    {
    case 1:
        printf("\n[전체 회원 목록]\n");
        for (User* p = user_head; p != NULL; p = p->next)
        {
            if (p->status)
            {
                printf("\n====================\n");
                printf("CHECK: 사용자\n");
                printf("ID   : %s\n", p->Id);
                printf("NAME : %s\n", p->name);
                printf("AGE  : %d\n", p->age);
                printf("PHONE: %s", p->Phone);
                printf("\n====================\n");
            }
            else
            {
                printf("\n====================\n");
                printf("CHECK: 관리자\n");
                printf("ID   : %s\n", p->Id);
                printf("NAME : %s\n", p->name);
                printf("AGE  : %d\n", p->age);
                printf("PHONE: %s", p->Phone);
                printf("\n====================\n");
            }
        }
        break;
    case 2:
        flag = 0;

        printf("\n[사용자 목록]\n");
        for (User* p = user_head; p != NULL; p = p->next)
        {
            if (p->status)  // 사용자일 때
            {
                flag = 1;
                printf("\n====================\n");
                printf("ID   : %s\n", p->Id);
                printf("NAME : %s\n", p->name);
                printf("AGE  : %d\n", p->age);
                printf("PHONE: %s", p->Phone);
                printf("\n====================\n");
            }

            if (flag == 0)
                printf("[등록된 사용자가 없습니다.]\n");
        }
        break;
    case 3:
        printf("\n[관리자 목록]\n");
        for (User* p = user_head; p != NULL; p = p->next)
        {
            if (p->status == 0)
            {
                printf("\n====================\n");
                printf("ID   : %s\n", p->Id);
                printf("NAME : %s\n", p->name);
                printf("AGE  : %d\n", p->age);
                printf("PHONE: %s", p->Phone);
                printf("\n====================\n");
            }
        }
        break;
    default:
        printf("\n[잘못 눌렀습니다.]\n");
        break;
    }
    return;
}

void delete_user()
{
    int flag;
    char* id = (char*)malloc(sizeof(char) * 20);
    User* p;

    while (1)
    {
        flag = 0;

        for (p = user_head; p != NULL; p = p->next)
        {
            if (p->status == 1)  // 사용자인 경우
                flag = 1;
        }

        if (flag == 0) {
            printf("[등록된 사용자가 없습니다.]\n");
            return;
        }

        printf("\n삭제회원의 아이디:");
        scanf(" %[^\n]", id);
        p = search_Id(id); //p = 삭제 회원의 User 구조체

        if (p == NULL)
        {
            printf("\n[해당 회원이 없습니다.]\n");
            return;
        }

        if (p->status)
            break;
        printf("[관리자는 삭제할 수 없습니다.]\n");
    }

    for (Movie* movie = movie_head; movie != NULL; movie = movie->next) //사용자가 Movie DB에 남긴 흔적 초기화
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(movie->size.Reserved_id[i], p->Id) == 0) //흔적이 있는 경우
            {
                (movie->reservated)--; //1 감소
                sprintf(movie->size.Reserved_id[i], "%d", i + 1); //다시 좌석 번호로 수정
                movie->size.seat[i] = 0; //1 -> 0 
            }
        }
    }

    if (p == user_head)
    {
        user_head = p->next;
        free(p);
    }
    else if (p == user_tail)
    {
        User* pre = search_pre_user(p);
        user_tail = pre;
        pre->next = NULL;
        free(p);
    }
    else // p구조체가 중간에
    {
        User* pre = search_pre_user(p);
        pre->next = p->next;
        free(p);
    }
    printf("\n[성공적으로 삭제되었습니다]\n");
    return;
}