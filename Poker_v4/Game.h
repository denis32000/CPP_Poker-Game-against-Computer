#pragma once

#include <windows.h>
#include <conio.h>
#include <cstdlib>

#include "Player.h" //// � ������������ �����
#include "Deck.h"   //// ������������ ������
#include "Table.h"  //// �� ���� ������
#include "Const.h"  ////

#include <string> ////������������  ������
#include <iostream> ////cout

class Game
{
private:
	int wins[2];//������ ������� ������

	Deck deck;//������ ����
	Table table;//����
	
	std::string Messages[HISTORY_MESSAGES]; ////using namespace std ����� �� ������

public:
	HumanPlayer user;//�������-�����
	ComputerPlayer computer;//���������-�����

	int activePlayer; //������ ������ ������ ������������ ����� ��������
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

	//������ ���� (������� ���� � �.�.)
	void startGame() 
	{
		deck.shuffle();

		user.startCards(deck);
		computer.startCards(deck);
		
		table.resetTable();//�������� ����

		lastAction = ACTION_NONE;
		dealNextCards = false;

		startStageBlind();//���� ������, ������ ������ - ������� (������ � ������)
		
/*DEBUG:
printf("�������� ����������� �����:\n"); 


��� �������� ������ ����������� ����������
����������������� ������ ���� ������������� ���� ����������� � ���������� ����������, � �������� ���� ����������� ����


//���������� ����-�����  5 ������� ���� ����� �����   #define ROYAL_FLUSH 28   (checkCombination ������ 28)
		Card card_1(12,1);
		Card card_2(0,3);//random
		Card card_3(11,1);
		Card card_4(5,1);//random
		Card card_5(10,1);

		Card card_6(9,1);
		Card card_7(8,1);

//���������� ����� ����  5 ���������������� ���� ����� �����      (checkCombination ������ 27)
		Card card_1(7,1);
		Card card_2(0,3);//random
		Card card_3(9,1);
		Card card_4(5,1);//random
		Card card_5(8,1);

		Card card_6(6,1);
		Card card_7(10,1);

//���������� ���� 4 ����� ������ �����      (checkCombination ������ 26, � ���������� 22, ������ ��� � ���� ������(3 ����� ����� �� ����� �����) )
		Card card_1(9,2);
		Card card_2(0,3);//random
		Card card_3(9,3);
		Card card_4(5,1);//random
		Card card_5(9,1);

		Card card_6(5,2);//random
		Card card_7(9,0);  

//���������� ���� ���� 3 ����� ������ ����� � 2 ����� ������� �����    (checkCombination ������ 25)
		Card card_1(9,2);
		Card card_2(0,3);//random
		Card card_3(9,3);
		Card card_4(5,1);//random
		Card card_5(2,1);

		Card card_6(5,2);//random
		Card card_7(9,0);  

//���������� ����  5 ���� ����� �����          (checkCombination ������ 24)
		Card card_1(9,2);
		Card card_2(0,3);//random
		Card card_3(6,2);
		Card card_4(5,1);//random
		Card card_5(2,2);

		Card card_6(5,2);//random
		Card card_7(7,2);

//���������� ����� 5 ���������������� ����              (checkCombination ������ 23)  
		Card card_1(9,2);
		Card card_2(0,3);//random
		Card card_3(7,2);
		Card card_4(4,1);//random
		Card card_5(8,1);

		Card card_6(6,2);//random
		Card card_7(10,1); 

//���������� ������ 3 ����� ������ �����              (checkCombination ������ 22)  
		Card card_1(9,2);
		Card card_2(0,3);//random
		Card card_3(9,3);
		Card card_4(5,1);//random
		Card card_5(2,1);

		Card card_6(4,2);//random
		Card card_7(9,0);  
		

//���������� ���� 2 ����� ������ �����
// +
//���������� ��� ���� 2 ����� ������ ����� � 2 �������           (checkCombination ������ 21 � ��������, � 20(1 ����) � ����������, ������ ��� �� ����� ��� ����� ���� ���� 1 ���� �����)  
		Card card_1(9,2);
		Card card_2(0,3);//random
		Card card_3(2,3);
		Card card_4(5,1);//random
		Card card_5(2,1);

		Card card_6(1,2);//random
		Card card_7(9,0);
		

��� �������� ������ ����������� ����������
����������������� ������ ���� ������������� ���� ����������� � ���������� ����������, � �������� ���� ����������� ����
		
		//����� �����
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

	void startStageBlind()//� ������� �� �����, ������ ������ ������ ������
	{
		writeToHistory("~ ���� ������, ������ � ������. (Blinds)");
		/*
		����� ������ ���� ������� (��� ������ ����), �������� ���� ������ � ������ (bet / fold)
			����� �������� �������, �������� ����� (call / raise / fold / allin)
		*/
		printTable();

		gamePart = STAGE_BLIND;

		PlayersTurn();

		startStageFlop();//��������� ����� �� ����
	}

	void startStageFlop()//������ �� ���� 3 �����
	{
		Sleep(1000);
		writeToHistory("~ ������ ���� � ���� ����. �� ����� ������� 3 �����. (Flop)");

		table.put_TableCards(deck,STAGE_FLOP);

		printTable();

		/*
		�� ����� �������� ����� � ���� ����������
		�� ����� ������ ����� ������ � ������� ������� ���������� (���� ������� allin)
			��������� ��������� ���� �����
				�������� ������ � �� ��������� ��������� �������� ��� ���������
				�������� ������ � �� ����� ��� ������
				������� ����� � ���� ����������
		*/

		gamePart = STAGE_FLOP;

		PlayersTurn();

		startStageTurn();//��������� ����� �� ����
	}
	
	void startStageTurn()//������ �� ���� 4 �����
	{
		Sleep(1000);
		writeToHistory("~ ������ ���� � ���� ����. �� ����� ������� 4 �����. (Turn)");

		table.put_TableCards(deck,STAGE_TURN);

		printTable();

		/*
		- ���� ������, �������� ��� �������� (raise / check / fold / allin)
	
		�� ����� �������� ����� � ���� ����������
		�� ����� ������� ����� ������ "��" � ������� ������� ����������
			��������� ��������� ���� ����� �:
				- �������� ������ � �� ��������� ��������� �������� ��� ���������
				- ������� ����� � ���� ����������
		�� ����� ���������� ���
			��������� ��������� ���� ����� �:
				- �������� ������ "��":
					��� ������ ������, � �� ����� ������� ��� ������������� (�������� ����� ����������� �� ��������� ����� � 1 �� �������)
				- ��������� ��� � �� ��������� ��������� �������� ��� ��������� (~ 50/50)
				- ������� ����� � ���� ���������� (~ <20)
		*/

		gamePart = STAGE_TURN;

		PlayersTurn();

		startStageRiver();//��������� ����� �� ����
	}
	
	void startStageRiver()//������ �� ���� 5 �����
	{	
		Sleep(1000);
		writeToHistory("~ ������ ���� � ���� ����. �� ����� ������� 5 �����. (River)");

		table.put_TableCards(deck,STAGE_RIVER);
		printTable();

		/*
		- ���� ������, �������� ��� �������� (raise / check / fold)
	
		�� ����� ������� ����� ������ "��" � ������� ������� ����������
			��������� ��������� ���� ����� �:
				- �������� ������ � �� ��������� ����������
				- ������� ����� � ���� ����������
		�� ����� ���������� ���
			��������� ��������� ���� ����� �:
				- �������� ������ "��":
					��� ������ ������, � �� ����� ������� ��� ������������� (�������� ����� ����������� �� ��������� ����� � 1 �� �������)
				- ��������� ��� � �� ��������� ����������
		*/

		gamePart = STAGE_RIVER;

		if(lastAction != ACTION_ALLIN) PlayersTurn();//���� ��� ���� ������ �� ���, ������ ����� ������ ������� ��� ������, ��� ��� ������ ��� ���������

		FinishGame(checkWinner());//����������� ����, � ���������� ����������
	}

	//������������� ��� �������, ��� �������� ��������, �� ������ ���������
	void PlayersTurn()
	{
		table.last_bet = 0; //����� ������ ����� ������� ����, �������� ��������� ������
		lastAction = ACTION_NONE;
		dealNextCards = false;//������� ��������� ������ ���� ����� ������� �������� ������� (���������� ����� true)

		do
		{
			//�������� ������:
			//���� ��� ������, � ���� �� ������ ��������� ���� ������ ��������, �������� �� ����� ���������
			//�� ���������� dealNextCards ����� ����� false, �������������, �� ����������� ����� ���������
			activePlayer = PLAYER_USER;
			user.getAction();

			if(dealNextCards == false)//���� ����� ���������, ���� ������ ����� �� ��������� ������
			{
				activePlayer = PLAYER_COMPUTER;
				computer.getAction();
			}
		}
		while(dealNextCards == false);//�������� ����� �� ��� ���, ���� ���������� dealNextCards �� ������ = true
	}

	int checkWinner()//������ �� ����������, ���������� ����������
	{
		int comb[2];

		comb[PLAYER_USER] = user.checkCombination();
		comb[PLAYER_COMPUTER] = computer.checkCombination();

		/* ���������������� ���� ��������, ����� ���������� ������ ���������� ����������
		printf("�������   %d \n", comb[PLAYER_USER]);
		printf("���������   %d \n", comb[PLAYER_COMPUTER]);
		*/

		if(comb[PLAYER_USER] > comb[PLAYER_COMPUTER]) return PLAYER_USER;
		else if(comb[PLAYER_USER] < comb[PLAYER_COMPUTER]) return PLAYER_COMPUTER;
		else return DRAW;
	}

	//��������� ������� ���� (����� �������� ��������� ������, ���� �������� ������)
	void FinishGame(int winner)
	{
		if(winner != DRAW) wins[winner]++;//���� �� �����, �� ��������� ������ ����������

		rewardGameWinner(winner);//���� ���������� ������ DRAW �� ������ �������

		printTable();
		
		
		std::cout << "\n\n======================================================================\n\n";
		std::cout << "����� �������!\n\n";

		if(winner == PLAYER_USER)
			std::cout << "���� �� ����� �������� ������������ � ����������� ���� " << user.combinationName() <<",\n������� ������ ��� ����������� � ����������� ���� " << computer.combinationName() << std::endl;
		else if(winner == PLAYER_COMPUTER)
			std::cout << "���� �� ����� �������� ��������� � ����������� ���� " << computer.combinationName() <<",\n������� ������ ��� ��������������� � ����������� ���� " << user.combinationName() << std::endl;
		else if(winner == DRAW)
			std::cout << "�����! ���������� ������������: "<< user.combinationName() << ", ���������� ����������: " << computer.combinationName() << ".\n���� ������� ������� ����� ������������� � ����������!\n";


		if(computer.money <= 0 || user.money <= 0)//���� � ����-�� ����������� ������, ����� ����
		{
			std::cout << "\n\n���� ��������! ������� ����� �������, ��� �� ����������...\n\n";
			std::cout << "======================================================================\n\n";
			_getch();

			system("cls");
			
			std::cout << "\n\n======================================================================\n\n";
			printf("���� ���������!\n\n");

			if(winner == PLAYER_USER) {
				printf("������������ ���������� ������ ��� ����������� �� ������ %d � %d\n",wins[winner], wins[PLAYER_COMPUTER]);
				printf("� �������� ���� � ��������� � %d ��������!\n\n", user.get_PlayerMoney());
				printf("������ �������!");
			}
			else {
				printf("��������� ���������� ������ ��� ������������� �� ������ %d � %d\n",wins[winner], wins[PLAYER_USER]);
				printf("� �������� ���� � ��������� � %d ��������!\n\n", computer.get_PlayerMoney());
				printf("������� � ��������� ���!");
			}
			std::cout << "\n\n======================================================================\n\n";

			exit(0);//��������� ���������
		}
		else //���� � ������� �������� ������, �� �������� ����� ������
		{
			std::cout << "\n������� ����� ������� ��� ������ ���������� ������!\n\n";
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
		else if(winner == DRAW)//���� �����
		{
			user.money += table.get_TableBank() / 2;
			computer.money += table.get_TableBank() / 2;
		}

		table.table_money = 0;
	}

	//����� ���������� � �����
	void printTable() 
	{
		system("cls");
		
		printf("������������ | %d � %d | ���������\n",wins[PLAYER_USER], wins[PLAYER_COMPUTER]);

		//���������� � �������
		printf("\n� ��� �� �����: (%d$) - ���� �� ������: %0.1f\n",user.get_PlayerMoney(), user.getWinPercent());

		for(int i = 0; i < 2; i++) {
			printf("\t %s \n", CardName[user.get_CardNum(i)]); }


		//����� ��� 5 ��� �� ����� � ���� ������ ��������, - ������ ��������� �����
		if(gamePart == STAGE_RIVER && lastAction == ACTION_ALLIN)
		{
			printf("\n� ���������� �� �����: (%d$) - ���� �� ������: %0.1f\n",computer.get_PlayerMoney(), computer.getWinPercent());

			for(int i = 0; i < 2; i++) {
				printf("\t %s \n", CardName[computer.get_CardNum(i)]); }
		}


		//���������� � �����
		printf("\n�� �����: (%d$)\n", table.get_TableBank());

		if(table.get_CardsOnTable() == 0) {
			printf("\t���� ���. ������ � ������.\n"); }
		else 
		{
			for(int i = 0; i < table.get_CardsOnTable(); i++) {
				printf("\t %s \n", CardName[table.get_CardNum(i)]);
			}
		}
		
		std::cout << std::endl;
		//������� ������� ��������� ��������
		for(int a = 0; a < HISTORY_MESSAGES; a++)
		{
			std::cout << Messages[a] << std::endl;
		}
		std::cout << std::endl;

		//DEBUG: ���������� ������ ����
		//deck._show();
	}

	void writeToHistory(std::string _text) 
	{
		//������� ��� ��������� �� 1 ����
		for(int a = 0; a < HISTORY_MESSAGES-1; a++)
		{
			Messages[a] = Messages[a+1];
		}

		//� ��������� ������ ���������� ��������� ���������
		if(_text[0] == '~') Messages[HISTORY_MESSAGES-1] = _text;
		else if(activePlayer == PLAYER_USER) Messages[HISTORY_MESSAGES-1] = "  ������������ " + _text;
		else if(activePlayer == PLAYER_COMPUTER) Messages[HISTORY_MESSAGES-1] = "  ��������� " + _text;

		printTable();
	}
};