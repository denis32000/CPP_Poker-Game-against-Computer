#pragma once 

//Общие константы
#define CARDS_COUNT 52 ////константы
#define START_MONEY 500 ////файл будет подключаться где нужно
#define HISTORY_MESSAGES 6

#define INVALID_CARD -1

//Типы комбинаций
//Пара - минимальное кол-во очков, начиная с 20
//Когда возвращает результат по высшей карте, то это полюбому будет до 20, ибо всего 12 рангов карт
#define PAIR 20
#define DOUBLE_PAIR 21
#define TROYKA 22
#define STREET 23
#define FLUSH 24
#define FULL_HOUSE 25
#define KARE 26
#define STREET_FLUSH 27
#define ROYAL_FLUSH 28

//Действия игрока
enum PlayerActions
{
	ACTION_NONE,	//Еще никаких действий небыло
	ACTION_CHECKED,	//Пропуск ставки
	ACTION_CALLED,	//Уравнивание ставки
	ACTION_FOLD,	//Сброс карт
	ACTION_RAISED,	//Поднятие ставки
	ACTION_ALLIN	//Ставка на все деньги
};

//Стадии игры
enum GameStages
{
	STAGE_BLIND,	//Ставки в слепую
	STAGE_FLOP,		//На столе 3 карты
	STAGE_TURN,		//На столе 4 карты
	STAGE_RIVER		//На столе 5 карт
};

enum Players
{
	PLAYER_USER,
	PLAYER_COMPUTER,
	DRAW //ничья
};
extern char CardName[52][32]; ////вот тут сложнее всего
                              ////объявляем, но не создаем массив