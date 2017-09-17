#include "StdAfx.h"
#include "Player.h"

#include "Const.h"

//#include <string>

#include "Card.h"
#include "Deck.h"
#include "Table.h"

#include "Game.h"

#include <conio.h> ////_getch

using namespace std;

string Player::combinationName()
{
	string _name;

	switch(checkCombination())
	{
	case 0: 
		_name = "Двойка";
		break;
	case 1: 
		_name = "Тройка";
		break;
	case 2: 
		_name = "Четверка";
		break;
	case 3: 
		_name = "Пятерка";
		break;
	case 4: 
		_name = "Шестерка";
		break;
	case 5: 
		_name = "Семерка";
		break;
	case 6: 
		_name = "Восьмерка";
		break;
	case 7: 
		_name = "Девятка";
		break;
	case 8: 
		_name = "Десятка";
		break;
	case 9: 
		_name = "Валет";
		break;
	case 10: 
		_name = "Дама";
		break;
	case 11: 
		_name = "Король";
		break;
	case 12: 
		_name = "Туз";
		break;
	case PAIR: 
		_name = "Пара";
		break;
	case DOUBLE_PAIR: 
		_name = "Двойная Пара";
		break;
	case TROYKA: _name = "Тройка Карт";
		break;
	case STREET: 
		_name = "Стрит";
		break;
	case FLUSH: 
		_name = "Флеш";
		break;
	case FULL_HOUSE: 
		_name = "Фулл-Хаус";
		break;
	case KARE: 
		_name = "Каре";
		break;
	case STREET_FLUSH: 
		_name = "Стрит-Флеш";
		break;
	case ROYAL_FLUSH: 
		_name = "Флеш-Рояль";
		break;
	}
	
	return _name;
}

int Player::checkCombination()
{
	Card _card;

	int score = 0;
	int block[7][2];
	
	block[0][0] = hand[0].get_Rank();
	block[0][1] = hand[0].get_Suit();
	
	block[1][0] = hand[1].get_Rank();
	block[1][1] = hand[1].get_Suit();

	for(int a = 0; a < 5; a++)//2 карты игрока мы уже закинули в массив, теперь кидаем туда карты со стола
	{
		_card = table -> tableCards[a];

		block[a+2][0] = _card.get_Rank();
		block[a+2][1] = _card.get_Suit();
	}

	//СОРТИРУЕМ РУКУ ПО ВОЗРАСТАНИЮ РАНГА КАРТЫ
	for(int i = 0; i < 7-1; i++)
	{
		for(int k = i+1; k < 7; k++)
		{
			if(block[i][0] > block[k][0])
			{
				int p1 = block[i][0], 
					p2 = block[i][1];

				block[i][0] = block[k][0];
				block[i][1] = block[k][1];

				block[k][0] = p1;
				block[k][1] = p2;
			}
		}
	}

	/*DEBUG:
	printf("сортировка\n");
	for(int a = 0; a < 7; a++)
	{
		printf("%d-%d\n",block[a][0],block[a][1]);
	}*/


	//Теперь начинаем проверять комбинации

	bool check = false;



	//ROYAL_FLUSH
	//Флеш-Рояль: 5 старших карт одной масти A,K,Q,J,10      
	check = false;

	for(int a = 0; a < 3; a++)//проверяем 3 первые карты (если одна из них - десятка, после нее должна быть очередь 4 карт)
	{
		int _suit = block[a][1];

		for(int j = 0; j < 5; j++)//проверяем 5 карт, т.к. первая карта(с первого цикла) проверяется включительно
		{
			if(block[a+j][0] == 8 + j  //порядок очереди соблюден: 8+0, 8+1, 8+2, 8+3, 8+4  
			&& block[a+j][1] == _suit//и масти совпадают
			&& block[a+j][0] != INVALID_CARD) 
			{	
				check = true;
			}
			else//очередь прервалась, - ломаем внутренний цикл, и проверяем очередь начиная со 2 карты
			{
				check = false;
				break; 
			}
		}
		if(check == true) break;//Уже нашли очередь из 5 карт
	}
	if(check == true) return ROYAL_FLUSH; //возвращаем комбинацию игрока
	




	//STREET_FLUSH
	//Стрит Флеш 5 последовательных карт одной масти.
	check = false;

	for(int a = 0; a < 3; a++)
	{
		int _suit = block[a][1];//запоминаем масть текущей пятерки карт
		
		for(int j = 0; j < 4; j++)//делаем цикл не на 5 тактов, а на 4, потому что в проверке a+j+1 (что бы проверить переднюю карту)
		{
			if( (block[a+j+1][0] - block[a+j][0]) <= 1//Если разница рангов соседних карт не превышает еденицу
			&& block[a+j][1] == _suit //и масти совпадают
			&& block[a+j][0] != INVALID_CARD)
			{	
				check = true;
			}
			else //очередь прервалась, - ломаем внутренний цикл, и проверяем очередь начиная со 2/3 карты
			{
				check = false;
				break; 
			}
		}
		if(check == true) break;//Уже нашли очередь из 5 карт
	}
	if(check == true) return STREET_FLUSH; //возвращаем комбинацию игрока



	//KARE
	//4 карты одного ранга

	int count = 1;//единице, потому что учитываем ранг текущей карты, как буд-то она уже начало комбо из 4 карт (аналогично во всех)

	for(int a = 0; a < 6; a++)//делаем 6 тактов, ибо 7 такт проверяется как +1 в проверке
	{
		if(block[a][0] == block[a+1][0] 
		&& block[a][0] != INVALID_CARD) 
		{
			count++;//если у текущей и следующей карты одинаковые ранги
			if(count == 4) return KARE;//Если 4 уже насчиталось, то прерываем цикл
		}
		else count = 1;
	}




	//FULL_HOUSE
	//3 карты одного ранга и пара
	int triple_rank = -1;
	count = 1;

	for(int a = 0; a < 6; a++)//делаем 6 тактов, ибо 7 такт проверяется как +1 в проверке
	{
		if(block[a][0] == block[a+1][0] && block[a][0] != INVALID_CARD) //если у текущей и следующей карты одинаковые ранги
		{
			triple_rank = block[a][0];//запоминаем ранг карты, которая будет повторяться 3 раза
			count++; 
			if(count == 3) break;//Если 3 уже насчиталось, то прерываем цикл
		}
		else 
		{
			triple_rank = -1;
			count = 1;
		}
	}

	if(count == 3) //3 карты уже нашли, ищем 2 одного ранга
	{
		count = 1;
		for(int a = 0; a < 6; a++)//делаем 6 тактов, ибо 7 такт проверяется как +1 в проверке
		{
			if(block[a][0] != triple_rank 
			&& block[a][0] == block[a+1][0]
			&& block[a][0] != INVALID_CARD) 
			{
				count++;//если у текущей и следующей карты одинаковые ранги
				if(count == 2) break;//Если 2 уже насчиталось, то прерываем цикл
			}
			else count = 1;
		}
		if(count == 2) return FULL_HOUSE;
	}


	//FLUSH
	//5 карт одной масти
	count = 0;

	for(int a = 0; a < 6; a++)
	{
		count = 0;
		for(int b = 0; b < 7; b++)
		{
			if(block[a][1] == block[b][1] //масти совпали
			&& block[a][0] != INVALID_CARD)
			{
				count++;
				if(count == 5) return FLUSH;
			}
		}
	}




	//STREET
	//5 последовательных карт
	count = 1;

	for(int a = 0; a < 6; a++)
	{
		if( block[a+1][0] - block[a][0] == 1 //Если разница рангов соседних карт не превышает единицу;
		&&  block[a][0] != INVALID_CARD)
			count++;

		else if( block[a+1][0] - block[a][0] > 1  //если разрыв, то сбрасываем комбо подряд идущих
			&&   block[a][0] != INVALID_CARD)
			count = 1;

		//   ( block[a+1][0] - block[a][0] < 1 )   //карты просто повторились, сбрасывать счетчик нет смысла

		if(count == 5) return STREET; //возвращаем комбинацию игрока
	}





	//TROYKA
	//3 карты одного ранга
	count = 1;

	for(int a = 0; a < 6; a++)//делаем 6 тактов, ибо 7 такт проверяется как +1 в проверке
	{
		if(block[a][0] == block[a+1][0]//если у текущей и следующей карты одинаковые ранги
		&& block[a][0] != INVALID_CARD) 
		{
			count++; 
			if(count == 3) return TROYKA;//Если 3 уже насчиталось, то прерываем цикл
		}
		else count = 1;
	}




	//DOUBLE_PAIR + PAIR
	//2 пары + определение одинарной пары (для олптимизации)
	count = 1;
	triple_rank = -1;

	for(int a = 0; a < 6; a++)//делаем 6 тактов, ибо 7 такт проверяется как +1 в проверке
	{
		if(block[a][0] == block[a+1][0] //если у текущей и следующей карты одинаковые ранги
		&& block[a][0] != INVALID_CARD)
		{
			count++; 
			if(count == 2) 
			{
				triple_rank = block[a][0];//запоминаем ранг первой пары
				break;//Если 2 уже насчиталось, то прерываем цикл
			}
		}
		else count = 1;
	}

	if(triple_rank != -1)//Если первая пара вообще была найдена
	{
		count = 1;

		for(int a = 0; a < 6; a++)//делаем 6 тактов, ибо 7 такт проверяется как +1 в проверке
		{
			if(block[a][0] != triple_rank 
			&& block[a][0] == block[a+1][0]
			&& block[a][0] != INVALID_CARD) 
			{
				count++;//если у текущей и следующей карты одинаковые ранги
				if(count == 2) break;//Если 2 уже насчиталось, то прерываем цикл
			}
			else count = 1;
		}

		if(count == 2) return DOUBLE_PAIR;//если еще 1 пара была найдена
		else return PAIR;//если не нашли вторую пару
	}



	//HIGH_CARD
	//Возвращаем просто ранг карты самой высокой, это будет как комбинация
	//Только номер комбинации начинается с 20, а ранг карты максимальной - 12
	if(hand[0].get_Rank() >= hand[1].get_Rank()) return hand[0].get_Rank();
	else return hand[1].get_Rank();
}

float Player::getWinPercent()
{
	float combination = float(checkCombination());

	//Пропорцией узнаем его примерную комбинацию

	if(combination >= 20)//есть какая-нибудь комбинация
		combination = (combination * 100) / ROYAL_FLUSH;

	else
		combination = (combination * 100) / PAIR;//12-tuz

	return combination;
}

void ComputerPlayer::getAction()
{
	Sleep(2000);

	int _lastAct = game -> lastAction;
	float percent = getWinPercent();

	if(_lastAct == ACTION_RAISED)//Если оппонент поднял ставку
	{
		if(percent < 10.0) 
		{
			if(money > table -> last_bet) //если не прийдется делать "на всё", то принимаем
				call();
			else 
				fold();
		}

		else if(percent < 94) call();

		else allin();
	}

	else if(_lastAct == ACTION_ALLIN) //Если оппонент ставил "на всё"
	{
		if(percent < 30)
		{
			if(table -> last_bet <= money * 0.3)//Если ставка меньше чем треть наших денег
				call();

			else fold();
		}

		else call();
	}

	else if(_lastAct == ACTION_CHECKED)
	{
		if(percent < 50)
			check();

		else if(percent < 90) raise(money / 4);//подымаем ставку на четверть своих денег

		else allin();
	}

	/*  int a;
		printf("\n- КОМПЬЮТЕР ТЕСТ выбирает действие (в ручную сейчас):\n");
		if(isButtonAvailable(ACTION_FOLD))	printf("\tF - Сбросить карты. (Fold)\n"); 
		if(isButtonAvailable(ACTION_RAISED)) printf("\tB - Ввести сумму для поднятия ставки. (Bet)\n");
		if(isButtonAvailable(ACTION_CALLED)) printf("\tY - Уровнять ставку оппонента. (Call)\n");
		if(isButtonAvailable(ACTION_CHECKED)) printf("\tC - Пропустить ход. (Check)\n");
		if(isButtonAvailable(ACTION_ALLIN))	printf("\tA - Ставка \"на все\". (All-In)\n");
		bool bad_key = false; //нажата неверная клавиша
		do//спрашиваем клавишу, пока не нажмет верную
		{
			a = _getch();

			if(isButtonAvailable(ACTION_FOLD)		 && a == 'f' || a == 'F') fold();
			else if(isButtonAvailable(ACTION_RAISED) && a == 'b' || a == 'B') raise();
			else if(isButtonAvailable(ACTION_CALLED) && a == 'y' || a == 'Y') call();
			else if(isButtonAvailable(ACTION_CHECKED)&& a == 'c' || a == 'C') check();
			else if(isButtonAvailable(ACTION_ALLIN)	 && a == 'a' || a == 'A') allin();
			else bad_key = true;//нажал недоступную клавишу
		}
		while(bad_key == true); */
}



void HumanPlayer::getAction()
{
	int a;
		
	//game -> activePlayer = 0;  //// плохо, это не ответственность игрока

	printf("\n- Нажмите одну из клавиш для действия:\n");

	if(isButtonAvailable(ACTION_FOLD))	printf("\tF - Сбросить карты. (Fold)\n"); 

	if(isButtonAvailable(ACTION_RAISED)) printf("\tB - Ввести сумму для поднятия ставки. (Bet)\n");

	if(isButtonAvailable(ACTION_CALLED)) printf("\tY - Уровнять ставку оппонента. (Call)\n");

	if(isButtonAvailable(ACTION_CHECKED)) printf("\tC - Пропустить ход. (Check)\n");

	if(isButtonAvailable(ACTION_ALLIN))	printf("\tA - Ставка \"на все\". (All-In)\n");
		

	bool bad_key = false; //нажата неверная клавиша

	do//спрашиваем клавишу, пока не нажмет верную
	{
		a = _getch();

		if(isButtonAvailable(ACTION_FOLD)		 && a == 'f' || a == 'F') fold();
		else if(isButtonAvailable(ACTION_RAISED) && a == 'b' || a == 'B') raise(0);
		else if(isButtonAvailable(ACTION_CALLED) && a == 'y' || a == 'Y') call();
		else if(isButtonAvailable(ACTION_CHECKED)&& a == 'c' || a == 'C') check();
		else if(isButtonAvailable(ACTION_ALLIN)	 && a == 'a' || a == 'A') allin();
		else bad_key = true;//нажал недоступную клавишу
	}
	while(bad_key == true);
}


bool Player::isButtonAvailable(int _action) const
{
	int part = game -> gamePart;
	int _lastAct = game -> lastAction;

	switch(_action)
	{
		case ACTION_FOLD://Кнопка сброса
		{
			//Если на столе еще нет 5 карт, ИЛИ если ставка поднята
			if(part < STAGE_RIVER 
				|| _lastAct == ACTION_RAISED 
				|| _lastAct == ACTION_ALLIN) return true;
			break;
		}
		case ACTION_RAISED:
		{
			//Если у него есть хоть какие-то деньги, и противник не поставил все деньги на кон, то клавиша поднятия ставки ему доступна
			if(money > 0 && _lastAct != ACTION_ALLIN) return true;
			break;
		}
		case ACTION_CALLED:
		{
			//Если ставка была повышена, И у игрока есть хоть какие то деньги
			//** Если оппонент сделал All-In то для меня по деньгам это может быть не All-in, а простое уравнивание
			if( (_lastAct == ACTION_RAISED || _lastAct == ACTION_ALLIN) && money > 0) return true;
			break;
		}
		case ACTION_CHECKED:
		{
			//Если ставка НЕ поднималась (и никто не ставил All-In)
			if(_lastAct != ACTION_RAISED 
			&& _lastAct != ACTION_ALLIN) return true;
			break;
		}
		case ACTION_ALLIN:
		{
			//Если есть хоть какие-то деньги
			if(money > 0 && _lastAct != ACTION_ALLIN) return true;//Если оппонент не делал оллин, в ином случае мы можем принять его вызов кнопкой "уравнять"
			break;
		}
	}
	return false;
}

void Player::check() 
{
	int last_act = game -> lastAction;
	/*
		Если последним действием был Пропуск, 
			либо никаких действий еще небыло,
			мы можем пропустить ход
	*/
	if(last_act == ACTION_CHECKED
	/*|| last_act == ACTION_NONE*/) game -> dealNextCards = true;//ACTION_NONE нельзя, потому что вдруг второй игрок захочет поднять после слепых ставок или после вашего пасса
	
	game -> writeToHistory(" пропустил ход.");

	game -> lastAction = ACTION_CHECKED;
}

void Player::call() 
{
	int last_act = game -> lastAction;
	/*
		Если хватает на полноценный call то снимаем нужную сумму с игрока
		Если денег не хватает, он делает all in и сразу сдаются 5 карт на стол
	*/
	if(last_act == ACTION_RAISED
	|| last_act == ACTION_ALLIN) 
	{
		if(money > table -> last_bet)//Если хватает денег для уравнивания - с лихвой (тоесть есть смысл потом спрашивать действие у компа)
		{
			game -> dealNextCards = true;//Можно раздавать следующие карты
			money -= table -> last_bet; //Снимаем деньги для уравненивания ставки

			table -> to_TableBank(table -> last_bet);

			string s_temp = "уровнял ставку, заплатив " + to_string( long long(table -> last_bet) ) + "$";
			game -> writeToHistory(s_temp);
			
			if(last_act == ACTION_ALLIN) game -> startStageRiver();//если оппонент делал олл ин, а нам хватило денег что бы просто уровнять, то наичнаем последнюю стадию игры

			last_act = ACTION_CALLED;
		}
		else//Если не хватает денег для уравнивания, то он делает ставку "на всё"
		{
			allin();

			game -> lastAction = ACTION_ALLIN;
		}
	}
}
	
void Player::fold() {
	/*
		Выводим сообщение и сбросе карт одного из игроков
		Отдаем деньги со стола победителю партии
		Отдаем поток обработки в метод FinishGame, где решается
			Если деньги одного из игроков закончились - игра заканчивается
			Если деньги остались, мы начинаем новую партию
	*/
	
	string s_temp = "сбросил карты, отдав победителю куш в " + to_string( long long(table -> table_money)) + "$";
	game -> writeToHistory(s_temp);

	//Отдаем текущий банк стола победителю
	if(game -> activePlayer == PLAYER_COMPUTER) game -> rewardGameWinner(PLAYER_USER);
	else if(game -> activePlayer == PLAYER_USER) game -> rewardGameWinner(PLAYER_COMPUTER);
	
	
	game -> lastAction = ACTION_FOLD;

	//дальше поток обработки передается в FinishGame (откуда может закончится игра полностью)
	if(game -> activePlayer == PLAYER_COMPUTER) game -> FinishGame(PLAYER_USER);
	else if(game -> activePlayer == PLAYER_USER) game -> FinishGame(PLAYER_COMPUTER);
}

void Player::raise(int sum) 
{
	int last_act = game -> lastAction;

	//int sum = 0;
	
	bool bad_key = false; //нажата неверная клавиша

	do//спрашиваем клавишу, пока не нажмет верную
	{
		if(sum == 0)//Когда поднимает игрок, - изначально сумма ==0, когда компьютер - сумма заранее известна
		{
			cout << "Введите сумму денег для поднятия ставки: ";
			cin >> sum;
		}

		if(sum <= 0) bad_key = true;//Если ввел неверное значение
		if( (table -> last_bet) + sum < money)//Если хватает денег что бы покрыть прошлое поднятие и осуществить текущее
		{
			money -= (table -> last_bet) + sum;//Снимаем ему денег столько, на сколько поднимал оппонент + текущее поднятие 
			
			table -> to_TableBank( (table -> last_bet) + sum);
			
			string s_temp = "поднял ставку, заплатив " + to_string( long long((table -> last_bet) + sum) ) + "$";
			game -> writeToHistory(s_temp);

			table -> last_bet = sum;//последней ставкой стало текущее поднятие

			game -> lastAction = ACTION_RAISED;
		}
		else if( (table -> last_bet) + sum >= money)//если он пытается поднять на сумму которая будет больше или на все его деньги, то он делает All-In
		{
			allin();
		}
	}
	while(bad_key == true);
}

void Player::allin() 
{		
	table -> to_TableBank(money);
			
	table -> last_bet = money;//последней ставкой стало текущее поднятие

	string s_temp = "поставил на кон все деньги, в сумме " + to_string( long long(money) ) + "$";
	money = 0;
	game -> writeToHistory(s_temp);

	//game -> dealNextCards = true;

	if(game -> lastAction == ACTION_ALLIN) game -> startStageRiver(); //если оппонент делал тоже оллин

	game -> lastAction = ACTION_ALLIN;
	//в ином случае пусть делает уравнивание, или сброс карт
}

