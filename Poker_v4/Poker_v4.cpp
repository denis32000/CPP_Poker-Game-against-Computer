// Poker_v4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include "conio.h"
#include "math.h"
#include <ctime>

//МОИ КЛАССЫ
#include "Card.h"
#include "Deck.h"
#include "Table.h"
#include "Player.h"
#include "Game.h"


#include "Const.h" ////вместо определения констант

using namespace std;

//########################## int main ##########################
int main()
{
	srand( time(0) );
	setlocale(LC_ALL,"rus");
	
	system("color 27");

	system("mode con cols=80 lines=50");

	Game PokerGame;

	PokerGame.startGame();
}
