#pragma once
#define length 20

typedef struct Resevation {
	char Title[length], Company[length]; //��ȭ ����
	int year; //���� ����
} Reservation;

typedef struct User {
	char Id[length], Pw[length]; //���̵�, ��й�ȣ
	char Phone[length], name[length]; //��ȭ��ȣ, �̸�
	int age, status; //����, �ź�
	int reservation; //���� ��
	struct User* next; //User �ʵ��� ������ ����ų ������
	Reservation* List; //��ȭ ���� ����
} User;