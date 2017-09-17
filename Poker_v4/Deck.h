#pragma once ////�� ���� ������������ ������ ������ ���� ������
             ////�� ����������� �������� ���� 2 � ����� ���

#include "Card.h" ////��� ���������� �����
#include "Const.h" ////���������� ����� ����������
#include <stdio.h> ////printf
#include <stdlib.h> ////rand

class Deck
{
private:
	Card cards[CARDS_COUNT];

	int card_number;//����� ������� �����
	
public:

	Deck() {
		card_number = CARDS_COUNT-1;//����� ������� �����
	}

	//���������� ������
	void shuffle() {
		char a[CARDS_COUNT]; 
		int z;

		for(int i = 0; i < CARDS_COUNT; i++) a[i] = 0;

		int k = 0;
		while(k < CARDS_COUNT) 
		{
			z = rand() % CARDS_COUNT;

			if(a[z]) continue;
			a[z] = 1;

			cards[k].set_Rank(z / 4);
			cards[k].set_Suit(z % 4);

			k++;
			/*
			������ ����� � ���� �����
			0 - ������ .. 12 - ���
			0 - ����� .. 4 - ����

			��������: 14 - ������� �����  (14/4 = 3 ����: ������� (4 ������), 14%4 = 2 => 3 �����: �����)
			*/
		}
		card_number = CARDS_COUNT-1;//����� ������� �����
	}

	//�������� ������� ����� � ������
	Card topCard() {
		return cards[card_number--];
	}

	//DEBUG: ���������� ������ ����
	void _show() 
	{
		for(int i = CARDS_COUNT-1; i > 0; i--) 
		{
			printf("%s \n", CardName[cards[i].get_Rank() * 4 + cards[i].get_Suit()]);
		}
	}
};

