#pragma once

#include <string>

#include "Card.h"  ////���������� ������
#include "Table.h" ////�� ������
#include "Deck.h"  ////

class Game; ////�� ���������� �����, � ������ ��� �������

class Player
{
protected:
	Game *game;
	Table *table;


public:
	Card hand[2];
	int money;

	Player() 
	{
		money = START_MONEY;
	}

	Player(Table *_table, Game *_game)
	{
		money = START_MONEY;

		table = _table;
		game = _game;
	}

	//������ ��������� ����� ������ �� ����
	void startCards(Deck &_deck) 
	{
		hand[0] = _deck.topCard();
		hand[1] = _deck.topCard();
	}
	
	void check();
	

	void call();
	
	
	void fold();
	

	void raise(int _sum);
	

	void allin(); 
	

	int checkCombination();

	std::string combinationName();

	//������ ������� ����� ������ �� ������ �� ���-�� ��������� ����������
	float getWinPercent();

	//������ ���������� ����� ����� �� ����� ��� ����������� ������������� *(��������: �������� �����) 
	int get_CardNum(int nom) {
		return hand[nom].get_Rank() * 4 + hand[nom].get_Suit();
	}

	int get_PlayerMoney() const {
		return money;
	}

	bool isButtonAvailable(int _action) const;
	

	void getAction();
};


//������-����������
class ComputerPlayer : public Player
{
public:
	
	ComputerPlayer(Table *_table, Game *_game): Player(_table, _game) {
	}
	
	void getAction();
};




//������-����������
class HumanPlayer : public Player
{
public:
	HumanPlayer(Table *_table, Game *_game): Player(_table, _game) {}

	void getAction();
	
};

