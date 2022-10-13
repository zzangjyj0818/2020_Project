#pragma once
#define SIZE 16
#define length 20

typedef struct Hall {
	int seat[SIZE]; //�¼� ��
	char Reserved_id[SIZE][length]; //����� ���̵��� �¼�
} Hall;

typedef struct Movie {
	char Title[length], Company[length]; //��ȭ ���� , ��޻�
	int year, reservated; //�������� , ���� ��
	Hall size; //��ȭ���� ���� (ũ��, ���� ���̵�)
	struct Movie* next; //Movie �ʵ��� ������ ����ų ������
} Movie;