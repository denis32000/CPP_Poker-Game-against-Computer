#pragma once 

//����� ���������
#define CARDS_COUNT 52 ////���������
#define START_MONEY 500 ////���� ����� ������������ ��� �����
#define HISTORY_MESSAGES 6

#define INVALID_CARD -1

//���� ����������
//���� - ����������� ���-�� �����, ������� � 20
//����� ���������� ��������� �� ������ �����, �� ��� �������� ����� �� 20, ��� ����� 12 ������ ����
#define PAIR 20
#define DOUBLE_PAIR 21
#define TROYKA 22
#define STREET 23
#define FLUSH 24
#define FULL_HOUSE 25
#define KARE 26
#define STREET_FLUSH 27
#define ROYAL_FLUSH 28

//�������� ������
enum PlayerActions
{
	ACTION_NONE,	//��� ������� �������� ������
	ACTION_CHECKED,	//������� ������
	ACTION_CALLED,	//����������� ������
	ACTION_FOLD,	//����� ����
	ACTION_RAISED,	//�������� ������
	ACTION_ALLIN	//������ �� ��� ������
};

//������ ����
enum GameStages
{
	STAGE_BLIND,	//������ � ������
	STAGE_FLOP,		//�� ����� 3 �����
	STAGE_TURN,		//�� ����� 4 �����
	STAGE_RIVER		//�� ����� 5 ����
};

enum Players
{
	PLAYER_USER,
	PLAYER_COMPUTER,
	DRAW //�����
};
extern char CardName[52][32]; ////��� ��� ������� �����
                              ////���������, �� �� ������� ������