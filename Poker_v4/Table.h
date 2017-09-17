#pragma once

#include "Card.h" ////
#include "Deck.h" ////

class Table
{
private:
	int crds_on_table;

public:
	Card tableCards[5];//5 Карт на столе
	int table_money;
	int last_bet;


	Table() {
		table_money = 0;
		last_bet = 0;
		crds_on_table = 0;
	}

	//Отчищает стол
	void resetTable()
	{
		table_money = 0;
		last_bet = 0;
		crds_on_table = 0;
	}

	//Раскидывает карты на стол
	void put_TableCards(Deck &_deck, int _gamepart) 
	{
		//if(tableCards[0].get_Rank() == -1)//Первый круг раздачи на стол
		//else if(crds_on_table == 3)//Второй круг раздачи на стол
		//else if(crds_on_table == 4)//Последняя общая карта на стол

		/*
		Делаем if/if/if потому что при ставке "на всё", мы можем сразу переключится на раздачу 5 карт
		следовательно нам нужно выдать помимо пятой карты, все предидущие
		*/
		if(_gamepart >= STAGE_FLOP && crds_on_table == 0)//если первая карта еще не выдана, а стейдж уже больше либо равн
		{
			tableCards[0] = _deck.topCard();
			tableCards[1] = _deck.topCard();
			tableCards[2] = _deck.topCard();

			crds_on_table = 3;
		}

		if(_gamepart >= STAGE_TURN && crds_on_table == 3)//если на столе 3 карты а стейдж тёрн
		{
			tableCards[3] = _deck.topCard();
			crds_on_table = 4;
		}

		if(_gamepart == STAGE_RIVER && crds_on_table == 4)//если на столе 4 карты
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

