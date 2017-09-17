#pragma once

#include "Card.h" ////
#include "Deck.h" ////

class Table
{
private:
	int crds_on_table;

public:
	Card tableCards[5];//5 ���� �� �����
	int table_money;
	int last_bet;


	Table() {
		table_money = 0;
		last_bet = 0;
		crds_on_table = 0;
	}

	//�������� ����
	void resetTable()
	{
		table_money = 0;
		last_bet = 0;
		crds_on_table = 0;
	}

	//����������� ����� �� ����
	void put_TableCards(Deck &_deck, int _gamepart) 
	{
		//if(tableCards[0].get_Rank() == -1)//������ ���� ������� �� ����
		//else if(crds_on_table == 3)//������ ���� ������� �� ����
		//else if(crds_on_table == 4)//��������� ����� ����� �� ����

		/*
		������ if/if/if ������ ��� ��� ������ "�� ��", �� ����� ����� ������������ �� ������� 5 ����
		������������� ��� ����� ������ ������ ����� �����, ��� ����������
		*/
		if(_gamepart >= STAGE_FLOP && crds_on_table == 0)//���� ������ ����� ��� �� ������, � ������ ��� ������ ���� ����
		{
			tableCards[0] = _deck.topCard();
			tableCards[1] = _deck.topCard();
			tableCards[2] = _deck.topCard();

			crds_on_table = 3;
		}

		if(_gamepart >= STAGE_TURN && crds_on_table == 3)//���� �� ����� 3 ����� � ������ ���
		{
			tableCards[3] = _deck.topCard();
			crds_on_table = 4;
		}

		if(_gamepart == STAGE_RIVER && crds_on_table == 4)//���� �� ����� 4 �����
		{
			tableCards[4] = _deck.topCard();
			crds_on_table = 5;
		}
	}

	int get_CardsOnTable() {
		return crds_on_table;
	}

	int get_TableBank() const {
		return table_money;
	}

	void to_TableBank(int _sum) {
		table_money += _sum;
	}
	
	int get_CardNum(int nom) {
		return tableCards[nom].get_Rank() * 4 + tableCards[nom].get_Suit();
	}
};

