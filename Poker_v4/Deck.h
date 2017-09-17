#pragma once ////во всех заголовочных файлах должен быть сторож
             ////не позволяющий включить файл 2 и более раз

#include "Card.h" ////Дек использует карту
#include "Const.h" ////используем общие объявления
#include <stdio.h> ////printf
#include <stdlib.h> ////rand

class Deck
{
private:
	Card cards[CARDS_COUNT];

	int card_number;//Номер верхней карты
	
public:

	Deck() {
		card_number = CARDS_COUNT-1;//Номер верхней карты
	}

	//Перемешать колоду
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
			Делаем масть и ранг карты
			0 - двойка .. 12 - туз
			0 - трефы .. 4 - пики

			Например: 14 - пятерка черви  (14/4 = 3 ранг: пятерка (4 строка), 14%4 = 2 => 3 масть: черви)
			*/
		}
		card_number = CARDS_COUNT-1;//Номер верхней карты
	}

	//получить верхнюю карту с колоды
	Card topCard() {
		return cards[card_number--];
	}

	//DEBUG: показывает колоду карт
	void _show() 
	{
		for(int i = CARDS_COUNT-1; i > 0; i--) 
		{
			printf("%s \n", CardName[cards[i].get_Rank() * 4 + cards[i].get_Suit()]);
		}
	}
};

