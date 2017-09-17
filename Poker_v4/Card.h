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

	//���������� ����� ����
	void set_Rank(int _rank) {
		rank = _rank;
	}
	
	//���������� ����� �����
	void set_Suit(int _suit) {
		suit = _suit;
	}
	
	//������ ���� �����
	int get_Rank() const {
		return rank;
	}
	
	//������ ����� �����
	int get_Suit() const {
		return suit;
	}
};

