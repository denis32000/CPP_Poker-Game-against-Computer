#pragma once

#include "Const.h"

class Card
{
private:
	int rank;
	int suit;

public:
	Card() {
		rank = INVALID_CARD;
		suit = INVALID_CARD;
	}

	//DEBUG
	Card(int _rank, int _suit) {
		rank = _rank;
		suit = _suit;
	}

	//Установить карте ранг
	void set_Rank(int _rank) {
		rank = _rank;
	}
	
	//Установить карте масть
	void set_Suit(int _suit) {
		suit = _suit;
	}
	
	//Узнать ранг карты
	int get_Rank() const {
		return rank;
	}
	
	//Узнать масть карты
	int get_Suit() const {
		return suit;
	}
};

