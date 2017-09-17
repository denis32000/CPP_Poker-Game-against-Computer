#pragma once

#include <windows.h>
#include <conio.h>
#include <cstdlib>

#include "Player.h" //// в заголовочном файле
#include "Deck.h"   //// используются классы
#include "Table.h"  //// из этих файлов
#include "Const.h"  ////

#include <string> ////используется  строка
#include <iostream> ////cout

class Game
{
private:
	int wins[2];//победы каждого игрока

	Deck deck;//Колода карт
	Table table;//Стол
	
	std::string Messages[HISTORY_MESSAGES]; ////using namespace std лучше не писать

public:
	HumanPlayer user;//Человек-игрок
	ComputerPlayer computer;//Компьютер-игрок

	int activePlayer; //какому игроку сейчас пердоставлен выбор действия
	int lastAction;
	int gamePart;

	bool dealNextCards;


	Game(): table(), user(&table, this), computer(&table, this)
	{
		lastAction = ACTION_NONE;
		dealNextCards = false;

		wins[PLAYER_USER] = 0;
		wins[PLAYER_COMPUTER] = 0;
	}

	//Начало игры (раздача карт и т.д.)
	void startGame() 
	{
		deck.shuffle();

		user.startCards(deck);
		computer.startCards(deck);
		
		table.resetTable();//отчищаем стол

		lastAction = ACTION_NONE;
		dealNextCards = false;

		startStageBlind();//Игра начата, первая стадия - блайнды (ставки в слепую)
		
/*DEBUG:
printf("ВНИМАНИЕ ПРОВЕРОЧНЫЙ РЕЖИМ:\n"); 


ДЛЯ ПРОВЕРКИ РАБОТЫ ОПРЕДЕЛЕНИЯ КОМБИНАЦИЙ
РАССКОМЕНТИРОВАТЬ ТОЛЬКО ОДНУ ИНИЦИАЛИЗАЦИЮ КАРТ ОТНОСЯЩИХСЯ К ИСПЫТУЕМОЙ КОМБИНАЦИИ, И ФРАГМЕНТ КОДА ПРИВЕДЕННЫЙ НИЖЕ


//КОМБИНАЦИЯ ФЛЕШ-РОЯЛЬ  5 старших карт одной масти   #define ROYAL_FLUSH 28   (checkCombination вернет 28)
		Card card_1(12,1);
		Card card_2(0,3);//random
		Card card_3(11,1);
		Card card_4(5,1);//random
		Card card_5(10,1);

		Card card_6(9,1);
		Card card_7(8,1);

//КОМБИНАЦИЯ Стрит Флеш  5 последовательных карт одной масти      (checkCombination вернет 27)
		Card card_1(7,1);
		Card card_2(0,3);//random
		Card card_3(9,1);
		Card card_4(5,1);//random
		Card card_5(8,1);

		Card card_6(6,1);
		Card card_7(10,1);

//КОМБИНАЦИЯ КАРЕ 4 карты одного ранга      (checkCombination вернет 26, а компьютеру 22, потому что у него тройка(3 общих карты на столе лежат) )
		Card card_1(9,2);
		Card card_2(0,3);//random
		Card card_3(9,3);
		Card card_4(5,1);//random
		Card card_5(9,1);

		Card card_6(5,2);//random
		Card card_7(9,0);  

//КОМБИНАЦИЯ Фулл Хаус 3 карты одного ранга и 2 карты другого ранга    (checkCombination вернет 25)
		Card card_1(9,2);
		Card card_2(0,3);//random
		Card card_3(9,3);
		Card card_4(5,1);//random
		Card card_5(2,1);

		Card card_6(5,2);//random
		Card card_7(9,0);  

//КОМБИНАЦИЯ Флеш  5 карт одной масти          (checkCombination вернет 24)
		Card card_1(9,2);
		Card card_2(0,3);//random
		Card card_3(6,2);
		Card card_4(5,1);//random
		Card card_5(2,2);

		Card card_6(5,2);//random
		Card card_7(7,2);

//КОМБИНАЦИЯ Стрит 5 последовательных карт              (checkCombination вернет 23)  
		Card card_1(9,2);
		Card card_2(0,3);//random
		Card card_3(7,2);
		Card card_4(4,1);//random
		Card card_5(8,1);

		Card card_6(6,2);//random
		Card card_7(10,1); 

//КОМБИНАЦИЯ Тройка 3 карты одного ранга              (checkCombination вернет 22)  
		Card card_1(9,2);
		Card card_2(0,3);//random
		Card card_3(9,3);
		Card card_4(5,1);//random
		Card card_5(2,1);

		Card card_6(4,2);//random
		Card card_7(9,0);  
		

//КОМБИНАЦИЯ пара 2 карты одного ранга
// +
//КОМБИНАЦИЯ Две Пары 2 карты одного ранга и 2 другого           (checkCombination вернет 21 у человека, и 20(1 пара) у компьютера, потому что на столе изх общих карт есть 1 пара двоек)  
		Card card_1(9,2);
		Card card_2(0,3);//random
		Card card_3(2,3);
		Card card_4(5,1);//random
		Card card_5(2,1);

		Card card_6(1,2);//random
		Card card_7(9,0);
		

ДЛЯ ПРОВЕРКИ РАБОТЫ ОПРЕДЕЛЕНИЯ КОМБИНАЦИЙ
РАССКОМЕНТИРОВАТЬ ТОЛЬКО ОДНУ ИНИЦИАЛИЗАЦИЮ КАРТ ОТНОСЯЩИХСЯ К ИСПЫТУЕМОЙ КОМБИНАЦИИ, И ФРАГМЕНТ КОДА ПРИВЕДЕННЫЙ НИЖЕ
		
		//карты компа
		Card card_8(1,3);//random
		Card card_9(3,1);//random

		table.tableCards[0] = card_1;
		table.tableCards[1] = card_2;
		table.tableCards[2] = card_3;
		table.tableCards[3] = card_4;
		table.tableCards[4] = card_5;

		user.hand[0] = card_6;
		user.hand[1] = card_7;

		computer.hand[0] = card_8;
		computer.hand[1] = card_9;

		printf("%d",checkWinner());

		system("pause");

		*/
	}

	void startStageBlind()//С картами на руках, игроки делают первые ставки
	{
		writeToHistory("~ Игра начата, ставки в слепую. (Blinds)");
		/*
		После выдачи карт игрокам (при старте игры), делается круг ставок в слепую (bet / fold)
			после действия игроком, оппонент может (call / raise / fold / allin)
		*/
		printTable();

		gamePart = STAGE_BLIND;

		PlayersTurn();

		startStageFlop();//Следующая карта на стол
	}

	void startStageFlop()//Кладем на стол 3 карты
	{
		Sleep(1000);
		writeToHistory("~ Ставки ушли в банк игры. На столе вскрыли 3 карты. (Flop)");

		table.put_TableCards(deck,STAGE_FLOP);

		printTable();

		/*
		Мы можем сбросить карты и игра закончится
		Мы можем ввести сумму ставки и ожидать реакцию компьютера (либо сделать allin)
			Компьютер определит свои шансы
				Уравняет ставку и мы продолжим выполнять основной код программы
				Поднимет ставку и мы дадим ход игроку
				Сбросит карты и игра закончится
		*/

		gamePart = STAGE_FLOP;

		PlayersTurn();

		startStageTurn();//Следующая карта на стол
	}
	
	void startStageTurn()//Кладем на стол 4 карту
	{
		Sleep(1000);
		writeToHistory("~ Ставки ушли в банк игры. На столе вскрыли 4 карту. (Turn)");

		table.put_TableCards(deck,STAGE_TURN);

		printTable();

		/*
		- Круг ставок, доступны все действия (raise / check / fold / allin)
	
		Мы можем сбросить карты и игра закончится
		Мы можем поднять сумму ставки "на" и ожидать реакцию компьютера
			Компьютер определит свои шансы и:
				- Уравняет ставку и мы продолжим выполнять основной код программы
				- Сбросит карты и игра закончится
		Мы можем пропустить ход
			Компьютер определит свои шансы и:
				- Поднимет ставку "на":
					Ход дается игроку, и он может сделать все вышесказанное (ОПЕРАЦИЯ МОЖЕТ ЗАЦИКЛИТЬСЯ ДО ОКОНЧАНИЯ ДЕНЕГ У 1 ИЗ ИГРОКОВ)
				- Пропустит ход и мы продолжим выполнять основной код программы (~ 50/50)
				- Сбросит карты и игра закончится (~ <20)
		*/

		gamePart = STAGE_TURN;

		PlayersTurn();

		startStageRiver();//Следующая карта на стол
	}
	
	void startStageRiver()//Кладем на стол 5 карту
	{	
		Sleep(1000);
		writeToHistory("~ Ставки ушли в банк игры. На столе вскрыли 5 карту. (River)");

		table.put_TableCards(deck,STAGE_RIVER);
		printTable();

		/*
		- Круг ставок, доступны все действия (raise / check / fold)
	
		Мы можем поднять сумму ставки "на" и ожидать реакцию компьютера
			Компьютер определит свои шансы и:
				- Уравняет ставку и мы ОПРЕДЕЛИМ ПОБЕДИТЕЛЯ
				- Сбросит карты и игра закончится
		Мы можем пропустить ход
			Компьютер определит свои шансы и:
				- Поднимет ставку "на":
					Ход дается игроку, и он может сделать все вышесказанное (ОПЕРАЦИЯ МОЖЕТ ЗАЦИКЛИТЬСЯ ДО ОКОНЧАНИЯ ДЕНЕГ У 1 ИЗ ИГРОКОВ)
				- Пропустит ход и мы ОПРЕДЕЛИМ ПОБЕДИТЕЛЯ
		*/

		gamePart = STAGE_RIVER;

		if(lastAction != ACTION_ALLIN) PlayersTurn();//Если это была ставка на все, давать право выбора игрокам нет смысла, ибо все деньги уже потрачены

		FinishGame(checkWinner());//Заканчиваем игру, и определяем победителя
	}

	//Предоставляем ход игрокам, они выбирают действие, из списка доступных
	void PlayersTurn()
	{
		table.last_bet = 0; //Перед каждой новой стадией игры, обнуляем последнюю ставку
		lastAction = ACTION_NONE;
		dealNextCards = false;//Раздать следующую партию карт когда совпали действия игроков (переменная равна true)

		do
		{
			//Описание логики:
			//Даем ход игроку, и если он делает повышение либо другое действие, влияющее не выбор оппонента
			//То переменная dealNextCards будет равна false, следовательно, мы предоставим выбор оппоненту
			activePlayer = PLAYER_USER;
			user.getAction();

			if(dealNextCards == false)//даем выбор оппоненту, если первый игрок не уравнивал ставку
			{
				activePlayer = PLAYER_COMPUTER;
				computer.getAction();
			}
		}
		while(dealNextCards == false);//Выбирать будут до тех пор, пока переменная dealNextCards не станет = true
	}

	int checkWinner()//исходя из комбинаций, определяем победителя
	{
		int comb[2];

		comb[PLAYER_USER] = user.checkCombination();
		comb[PLAYER_COMPUTER] = computer.checkCombination();

		/* раскоментировать этот фрагмент, когда проверяете работу нахождения комбинаций
		printf("ЧЕЛОВЕК   %d \n", comb[PLAYER_USER]);
		printf("КОМПЬЮТЕР   %d \n", comb[PLAYER_COMPUTER]);
		*/

		if(comb[PLAYER_USER] > comb[PLAYER_COMPUTER]) return PLAYER_USER;
		else if(comb[PLAYER_USER] < comb[PLAYER_COMPUTER]) return PLAYER_COMPUTER;
		else return DRAW;
	}

	//Окончание текущей игры (может начаться следующая партия, если остались деньги)
	void FinishGame(int winner)
	{
		if(winner != DRAW) wins[winner]++;//Если не ничья, то добавляем победы победителю

		rewardGameWinner(winner);//если аргументом станет DRAW то деньги поделит

		printTable();
		
		
		std::cout << "\n\n======================================================================\n\n";
		std::cout << "Раунд окончен!\n\n";

		if(winner == PLAYER_USER)
			std::cout << "Банк со стола забирает пользователь с комбинацией карт " << user.combinationName() <<",\nодержав победу над компьютером с комбинацией карт " << computer.combinationName() << std::endl;
		else if(winner == PLAYER_COMPUTER)
			std::cout << "Банк со стола забирает компьютер с комбинацией карт " << computer.combinationName() <<",\nодержав победу над пользователелем с комбинацией карт " << user.combinationName() << std::endl;
		else if(winner == DRAW)
			std::cout << "Ничья! Комбинация пользователя: "<< user.combinationName() << ", комбинация компьютера: " << computer.combinationName() << ".\nБанк поделен поровну между пользователем и компьтером!\n";


		if(computer.money <= 0 || user.money <= 0)//Если у кого-то закончились деньги, пишет итог
		{
			std::cout << "\n\nИгра окончена! Нажмите любую клавишу, что бы продолжить...\n\n";
			std::cout << "======================================================================\n\n";
			_getch();

			system("cls");
			
			std::cout << "\n\n======================================================================\n\n";
			printf("Игра закончена!\n\n");

			if(winner == PLAYER_USER) {
				printf("Пользователь одерживает победу над Компьютером со счетом %d — %d\n",wins[winner], wins[PLAYER_COMPUTER]);
				printf("и покидает стол с выигрышем в %d долларов!\n\n", user.get_PlayerMoney());
				printf("Хорошо сыграно!");
			}
			else {
				printf("Компьютер одерживает победу над Пользователем со счетом %d — %d\n",wins[winner], wins[PLAYER_USER]);
				printf("и покидает стол с выигрышем в %d долларов!\n\n", computer.get_PlayerMoney());
				printf("Повезет в следующий раз!");
			}
			std::cout << "\n\n======================================================================\n\n";

			exit(0);//Выключаем программу
		}
		else //Если у игроков остались деньги, то начинаем новую партию
		{
			std::cout << "\nНажмите любую клавишу для начала следующего раунда!\n\n";
			std::cout << "======================================================================\n\n";

			_getch();

			system("cls");

			startGame();
		}
	}

	void rewardGameWinner(int winner)
	{
		if(winner == PLAYER_USER) user.money += table.get_TableBank();
		else if(winner == PLAYER_COMPUTER) computer.money += table.get_TableBank();
		else if(winner == DRAW)//Если ничья
		{
			user.money += table.get_TableBank() / 2;
			computer.money += table.get_TableBank() / 2;
		}

		table.table_money = 0;
	}

	//Вывод информации о столе
	void printTable() 
	{
		system("cls");
		
		printf("Пользователь | %d — %d | Компьютер\n",wins[PLAYER_USER], wins[PLAYER_COMPUTER]);

		//Информация о игроках
		printf("\nУ Вас на руках: (%d$) - Шанс на победу: %0.1f\n",user.get_PlayerMoney(), user.getWinPercent());

		for(int i = 0; i < 2; i++) {
			printf("\t %s \n", CardName[user.get_CardNum(i)]); }


		//Когда уже 5 крт на столе и круг ставок завершен, - игроки вскрывают карты
		if(gamePart == STAGE_RIVER && lastAction == ACTION_ALLIN)
		{
			printf("\nУ компьютера на руках: (%d$) - Шанс на победу: %0.1f\n",computer.get_PlayerMoney(), computer.getWinPercent());

			for(int i = 0; i < 2; i++) {
				printf("\t %s \n", CardName[computer.get_CardNum(i)]); }
		}


		//Информация о столе
		printf("\nНа столе: (%d$)\n", table.get_TableBank());

		if(table.get_CardsOnTable() == 0) {
			printf("\tКарт нет. Ставки в слепую.\n"); }
		else 
		{
			for(int i = 0; i < table.get_CardsOnTable(); i++) {
				printf("\t %s \n", CardName[table.get_CardNum(i)]);
			}
		}
		
		std::cout << std::endl;
		//Выводит историю последних действий
		for(int a = 0; a < HISTORY_MESSAGES; a++)
		{
			std::cout << Messages[a] << std::endl;
		}
		std::cout << std::endl;

		//DEBUG: Показывает колоду карт
		//deck._show();
	}

	void writeToHistory(std::string _text) 
	{
		//Смещаем все сообщения на 1 вниз
		for(int a = 0; a < HISTORY_MESSAGES-1; a++)
		{
			Messages[a] = Messages[a+1];
		}

		//В последнюю ячейку записываем последнее сообщение
		if(_text[0] == '~') Messages[HISTORY_MESSAGES-1] = _text;
		else if(activePlayer == PLAYER_USER) Messages[HISTORY_MESSAGES-1] = "  Пользователь " + _text;
		else if(activePlayer == PLAYER_COMPUTER) Messages[HISTORY_MESSAGES-1] = "  Компьютер " + _text;

		printTable();
	}
};