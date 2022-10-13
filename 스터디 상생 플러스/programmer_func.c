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
        printf("��ȭ ���� : ");
        scanf(" %[^\n]", movie->Title);

        if ((movie_title_compare(movie->Title)))
            break;
        else
            printf("�̹� ��ϵ� ��ȭ�Դϴ�\n");
    }
    printf("���� ���� : ");
    scanf("%d", &movie->year);
    printf("��޻�: ");
    scanf(" %[^\n]", movie->Company);

    printf("\n=======================\n");

    char arr[16][3] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16" };

    for (int i = 0; i < 16; i++)
    {
        movie->size.seat[i] = 0;
        strcpy(movie->size.Reserved_id[i], arr[i]);
    }
    printf("<%s>�� ��ϵǾ����ϴ�.\n", movie->Title);
    for (int i = 0; i < 2; i++)
        Sleep(1000);
    system("cls");
}

int movie_title_compare(char* title)
{
    for (Movie* p = movie_head; p != movie_tail; p = p->next) //movie_tail = �Է¹ް� �ִ� ����
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
        printf("\n[��ȭ DB�� �����Ͱ� �����ϴ�.]\n");
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
    printf("\n[���������� �����Ǿ����ϴ�.]\n");
}

void user_management()
{
    int num;
    printf("\n(1)ȸ�� ����Ʈ ��� (2)ȸ�� ����");
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
        printf("\n[�߸� �������ϴ�.]\n");
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
    return pre;  //pre = p���� ����ü
}
// user print // for programmer
void print_user_list()
{
    int num, flag;
    if (user_head == NULL)
    {
        printf("\n[��ϵ� ȸ���� �����ϴ�.]\n");
        return;
    }

    printf("(1)��ü ���  (2)����� ���  (3)������ ���");
    printf("\n==>");
    scanf("%d", &num);

    switch (num)
    {
    case 1:
        printf("\n[��ü ȸ�� ���]\n");
        for (User* p = user_head; p != NULL; p = p->next)
        {
            if (p->status)
            {
                printf("\n====================\n");
                printf("CHECK: �����\n");
                printf("ID   : %s\n", p->Id);
                printf("NAME : %s\n", p->name);
                printf("AGE  : %d\n", p->age);
                printf("PHONE: %s", p->Phone);
                printf("\n====================\n");
            }
            else
            {
                printf("\n====================\n");
                printf("CHECK: ������\n");
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

        printf("\n[����� ���]\n");
        for (User* p = user_head; p != NULL; p = p->next)
        {
            if (p->status)  // ������� ��
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
                printf("[��ϵ� ����ڰ� �����ϴ�.]\n");
        }
        break;
    case 3:
        printf("\n[������ ���]\n");
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
        printf("\n[�߸� �������ϴ�.]\n");
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
            if (p->status == 1)  // ������� ���
                flag = 1;
        }

        if (flag == 0) {
            printf("[��ϵ� ����ڰ� �����ϴ�.]\n");
            return;
        }

        printf("\n����ȸ���� ���̵�:");
        scanf(" %[^\n]", id);
        p = search_Id(id); //p = ���� ȸ���� User ����ü

        if (p == NULL)
        {
            printf("\n[�ش� ȸ���� �����ϴ�.]\n");
            return;
        }

        if (p->status)
            break;
        printf("[�����ڴ� ������ �� �����ϴ�.]\n");
    }

    for (Movie* movie = movie_head; movie != NULL; movie = movie->next) //����ڰ� Movie DB�� ���� ���� �ʱ�ȭ
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(movie->size.Reserved_id[i], p->Id) == 0) //������ �ִ� ���
            {
                (movie->reservated)--; //1 ����
                sprintf(movie->size.Reserved_id[i], "%d", i + 1); //�ٽ� �¼� ��ȣ�� ����
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
    else // p����ü�� �߰���
    {
        User* pre = search_pre_user(p);
        pre->next = p->next;
        free(p);
    }
    printf("\n[���������� �����Ǿ����ϴ�]\n");
    return;
}