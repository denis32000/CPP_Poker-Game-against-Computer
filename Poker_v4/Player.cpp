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
		_name = "������";
		break;
	case 1: 
		_name = "������";
		break;
	case 2: 
		_name = "��������";
		break;
	case 3: 
		_name = "�������";
		break;
	case 4: 
		_name = "��������";
		break;
	case 5: 
		_name = "�������";
		break;
	case 6: 
		_name = "���������";
		break;
	case 7: 
		_name = "�������";
		break;
	case 8: 
		_name = "�������";
		break;
	case 9: 
		_name = "�����";
		break;
	case 10: 
		_name = "����";
		break;
	case 11: 
		_name = "������";
		break;
	case 12: 
		_name = "���";
		break;
	case PAIR: 
		_name = "����";
		break;
	case DOUBLE_PAIR: 
		_name = "������� ����";
		break;
	case TROYKA: _name = "������ ����";
		break;
	case STREET: 
		_name = "�����";
		break;
	case FLUSH: 
		_name = "����";
		break;
	case FULL_HOUSE: 
		_name = "����-����";
		break;
	case KARE: 
		_name = "����";
		break;
	case STREET_FLUSH: 
		_name = "�����-����";
		break;
	case ROYAL_FLUSH: 
		_name = "����-�����";
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

	for(int a = 0; a < 5; a++)//2 ����� ������ �� ��� �������� � ������, ������ ������ ���� ����� �� �����
	{
		_card = table -> tableCards[a];

		block[a+2][0] = _card.get_Rank();
		block[a+2][1] = _card.get_Suit();
	}

	//��������� ���� �� ����������� ����� �����
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
	printf("����������\n");
	for(int a = 0; a < 7; a++)
	{
		printf("%d-%d\n",block[a][0],block[a][1]);
	}*/


	//������ �������� ��������� ����������

	bool check = false;



	//ROYAL_FLUSH
	//����-�����: 5 ������� ���� ����� ����� A,K,Q,J,10      
	check = false;

	for(int a = 0; a < 3; a++)//��������� 3 ������ ����� (���� ���� �� ��� - �������, ����� ��� ������ ���� ������� 4 ����)
	{
		int _suit = block[a][1];

		for(int j = 0; j < 5; j++)//��������� 5 ����, �.�. ������ �����(� ������� �����) ����������� ������������
		{
			if(block[a+j][0] == 8 + j  //������� ������� ��������: 8+0, 8+1, 8+2, 8+3, 8+4  
			&& block[a+j][1] == _suit//� ����� ���������
			&& block[a+j][0] != INVALID_CARD) 
			{	
				check = true;
			}
			else//������� ����������, - ������ ���������� ����, � ��������� ������� ������� �� 2 �����
			{
				check = false;
				break; 
			}
		}
		if(check == true) break;//��� ����� ������� �� 5 ����
	}
	if(check == true) return ROYAL_FLUSH; //���������� ���������� ������
	




	//STREET_FLUSH
	//����� ���� 5 ���������������� ���� ����� �����.
	check = false;

	for(int a = 0; a < 3; a++)
	{
		int _suit = block[a][1];//���������� ����� ������� ������� ����
		
		for(int j = 0; j < 4; j++)//������ ���� �� �� 5 ������, � �� 4, ������ ��� � �������� a+j+1 (��� �� ��������� �������� �����)
		{
			if( (block[a+j+1][0] - block[a+j][0]) <= 1//���� ������� ������ �������� ���� �� ��������� �������
			&& block[a+j][1] == _suit //� ����� ���������
			&& block[a+j][0] != INVALID_CARD)
			{	
				check = true;
			}
			else //������� ����������, - ������ ���������� ����, � ��������� ������� ������� �� 2/3 �����
			{
				check = false;
				break; 
			}
		}
		if(check == true) break;//��� ����� ������� �� 5 ����
	}
	if(check == true) return STREET_FLUSH; //���������� ���������� ������



	//KARE
	//4 ����� ������ �����

	int count = 1;//�������, ������ ��� ��������� ���� ������� �����, ��� ���-�� ��� ��� ������ ����� �� 4 ���� (���������� �� ����)

	for(int a = 0; a < 6; a++)//������ 6 ������, ��� 7 ���� ����������� ��� +1 � ��������
	{
		if(block[a][0] == block[a+1][0] 
		&& block[a][0] != INVALID_CARD) 
		{
			count++;//���� � ������� � ��������� ����� ���������� �����
			if(count == 4) return KARE;//���� 4 ��� �����������, �� ��������� ����
		}
		else count = 1;
	}




	//FULL_HOUSE
	//3 ����� ������ ����� � ����
	int triple_rank = -1;
	count = 1;

	for(int a = 0; a < 6; a++)//������ 6 ������, ��� 7 ���� ����������� ��� +1 � ��������
	{
		if(block[a][0] == block[a+1][0] && block[a][0] != INVALID_CARD) //���� � ������� � ��������� ����� ���������� �����
		{
			triple_rank = block[a][0];//���������� ���� �����, ������� ����� ����������� 3 ����
			count++; 
			if(count == 3) break;//���� 3 ��� �����������, �� ��������� ����
		}
		else 
		{
			triple_rank = -1;
			count = 1;
		}
	}

	if(count == 3) //3 ����� ��� �����, ���� 2 ������ �����
	{
		count = 1;
		for(int a = 0; a < 6; a++)//������ 6 ������, ��� 7 ���� ����������� ��� +1 � ��������
		{
			if(block[a][0] != triple_rank 
			&& block[a][0] == block[a+1][0]
			&& block[a][0] != INVALID_CARD) 
			{
				count++;//���� � ������� � ��������� ����� ���������� �����
				if(count == 2) break;//���� 2 ��� �����������, �� ��������� ����
			}
			else count = 1;
		}
		if(count == 2) return FULL_HOUSE;
	}


	//FLUSH
	//5 ���� ����� �����
	count = 0;

	for(int a = 0; a < 6; a++)
	{
		count = 0;
		for(int b = 0; b < 7; b++)
		{
			if(block[a][1] == block[b][1] //����� �������
			&& block[a][0] != INVALID_CARD)
			{
				count++;
				if(count == 5) return FLUSH;
			}
		}
	}




	//STREET
	//5 ���������������� ����
	count = 1;

	for(int a = 0; a < 6; a++)
	{
		if( block[a+1][0] - block[a][0] == 1 //���� ������� ������ �������� ���� �� ��������� �������;
		&&  block[a][0] != INVALID_CARD)
			count++;

		else if( block[a+1][0] - block[a][0] > 1  //���� ������, �� ���������� ����� ������ ������
			&&   block[a][0] != INVALID_CARD)
			count = 1;

		//   ( block[a+1][0] - block[a][0] < 1 )   //����� ������ �����������, ���������� ������� ��� ������

		if(count == 5) return STREET; //���������� ���������� ������
	}





	//TROYKA
	//3 ����� ������ �����
	count = 1;

	for(int a = 0; a < 6; a++)//������ 6 ������, ��� 7 ���� ����������� ��� +1 � ��������
	{
		if(block[a][0] == block[a+1][0]//���� � ������� � ��������� ����� ���������� �����
		&& block[a][0] != INVALID_CARD) 
		{
			count++; 
			if(count == 3) return TROYKA;//���� 3 ��� �����������, �� ��������� ����
		}
		else count = 1;
	}




	//DOUBLE_PAIR + PAIR
	//2 ���� + ����������� ��������� ���� (��� ������������)
	count = 1;
	triple_rank = -1;

	for(int a = 0; a < 6; a++)//������ 6 ������, ��� 7 ���� ����������� ��� +1 � ��������
	{
		if(block[a][0] == block[a+1][0] //���� � ������� � ��������� ����� ���������� �����
		&& block[a][0] != INVALID_CARD)
		{
			count++; 
			if(count == 2) 
			{
				triple_rank = block[a][0];//���������� ���� ������ ����
				break;//���� 2 ��� �����������, �� ��������� ����
			}
		}
		else count = 1;
	}

	if(triple_rank != -1)//���� ������ ���� ������ ���� �������
	{
		count = 1;

		for(int a = 0; a < 6; a++)//������ 6 ������, ��� 7 ���� ����������� ��� +1 � ��������
		{
			if(block[a][0] != triple_rank 
			&& block[a][0] == block[a+1][0]
			&& block[a][0] != INVALID_CARD) 
			{
				count++;//���� � ������� � ��������� ����� ���������� �����
				if(count == 2) break;//���� 2 ��� �����������, �� ��������� ����
			}
			else count = 1;
		}

		if(count == 2) return DOUBLE_PAIR;//���� ��� 1 ���� ���� �������
		else return PAIR;//���� �� ����� ������ ����
	}



	//HIGH_CARD
	//���������� ������ ���� ����� ����� �������, ��� ����� ��� ����������
	//������ ����� ���������� ���������� � 20, � ���� ����� ������������ - 12
	if(hand[0].get_Rank() >= hand[1].get_Rank()) return hand[0].get_Rank();
	else return hand[1].get_Rank();
}

float Player::getWinPercent()
{
	float combination = float(checkCombination());

	//���������� ������ ��� ��������� ����������

	if(combination >= 20)//���� �����-������ ����������
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

	if(_lastAct == ACTION_RAISED)//���� �������� ������ ������
	{
		if(percent < 10.0) 
		{
			if(money > table -> last_bet) //���� �� ��������� ������ "�� ��", �� ���������
				call();
			else 
				fold();
		}

		else if(percent < 94) call();

		else allin();
	}

	else if(_lastAct == ACTION_ALLIN) //���� �������� ������ "�� ��"
	{
		if(percent < 30)
		{
			if(table -> last_bet <= money * 0.3)//���� ������ ������ ��� ����� ����� �����
				call();

			else fold();
		}

		else call();
	}

	else if(_lastAct == ACTION_CHECKED)
	{
		if(percent < 50)
			check();

		else if(percent < 90) raise(money / 4);//�������� ������ �� �������� ����� �����

		else allin();
	}

	/*  int a;
		printf("\n- ��������� ���� �������� �������� (� ������ ������):\n");
		if(isButtonAvailable(ACTION_FOLD))	printf("\tF - �������� �����. (Fold)\n"); 
		if(isButtonAvailable(ACTION_RAISED)) printf("\tB - ������ ����� ��� �������� ������. (Bet)\n");
		if(isButtonAvailable(ACTION_CALLED)) printf("\tY - �������� ������ ���������. (Call)\n");
		if(isButtonAvailable(ACTION_CHECKED)) printf("\tC - ���������� ���. (Check)\n");
		if(isButtonAvailable(ACTION_ALLIN))	printf("\tA - ������ \"�� ���\". (All-In)\n");
		bool bad_key = false; //������ �������� �������
		do//���������� �������, ���� �� ������ ������
		{
			a = _getch();

			if(isButtonAvailable(ACTION_FOLD)		 && a == 'f' || a == 'F') fold();
			else if(isButtonAvailable(ACTION_RAISED) && a == 'b' || a == 'B') raise();
			else if(isButtonAvailable(ACTION_CALLED) && a == 'y' || a == 'Y') call();
			else if(isButtonAvailable(ACTION_CHECKED)&& a == 'c' || a == 'C') check();
			else if(isButtonAvailable(ACTION_ALLIN)	 && a == 'a' || a == 'A') allin();
			else bad_key = true;//����� ����������� �������
		}
		while(bad_key == true); */
}



void HumanPlayer::getAction()
{
	int a;
		
	//game -> activePlayer = 0;  //// �����, ��� �� ��������������� ������

	printf("\n- ������� ���� �� ������ ��� ��������:\n");

	if(isButtonAvailable(ACTION_FOLD))	printf("\tF - �������� �����. (Fold)\n"); 

	if(isButtonAvailable(ACTION_RAISED)) printf("\tB - ������ ����� ��� �������� ������. (Bet)\n");

	if(isButtonAvailable(ACTION_CALLED)) printf("\tY - �������� ������ ���������. (Call)\n");

	if(isButtonAvailable(ACTION_CHECKED)) printf("\tC - ���������� ���. (Check)\n");

	if(isButtonAvailable(ACTION_ALLIN))	printf("\tA - ������ \"�� ���\". (All-In)\n");
		

	bool bad_key = false; //������ �������� �������

	do//���������� �������, ���� �� ������ ������
	{
		a = _getch();

		if(isButtonAvailable(ACTION_FOLD)		 && a == 'f' || a == 'F') fold();
		else if(isButtonAvailable(ACTION_RAISED) && a == 'b' || a == 'B') raise(0);
		else if(isButtonAvailable(ACTION_CALLED) && a == 'y' || a == 'Y') call();
		else if(isButtonAvailable(ACTION_CHECKED)&& a == 'c' || a == 'C') check();
		else if(isButtonAvailable(ACTION_ALLIN)	 && a == 'a' || a == 'A') allin();
		else bad_key = true;//����� ����������� �������
	}
	while(bad_key == true);
}


bool Player::isButtonAvailable(int _action) const
{
	int part = game -> gamePart;
	int _lastAct = game -> lastAction;

	switch(_action)
	{
		case ACTION_FOLD://������ ������
		{
			//���� �� ����� ��� ��� 5 ����, ��� ���� ������ �������
			if(part < STAGE_RIVER 
				|| _lastAct == ACTION_RAISED 
				|| _lastAct == ACTION_ALLIN) return true;
			break;
		}
		case ACTION_RAISED:
		{
			//���� � ���� ���� ���� �����-�� ������, � ��������� �� �������� ��� ������ �� ���, �� ������� �������� ������ ��� ��������
			if(money > 0 && _lastAct != ACTION_ALLIN) return true;
			break;
		}
		case ACTION_CALLED:
		{
			//���� ������ ���� ��������, � � ������ ���� ���� ����� �� ������
			//** ���� �������� ������ All-In �� ��� ���� �� ������� ��� ����� ���� �� All-in, � ������� �����������
			if( (_lastAct == ACTION_RAISED || _lastAct == ACTION_ALLIN) && money > 0) return true;
			break;
		}
		case ACTION_CHECKED:
		{
			//���� ������ �� ����������� (� ����� �� ������ All-In)
			if(_lastAct != ACTION_RAISED 
			&& _lastAct != ACTION_ALLIN) return true;
			break;
		}
		case ACTION_ALLIN:
		{
			//���� ���� ���� �����-�� ������
			if(money > 0 && _lastAct != ACTION_ALLIN) return true;//���� �������� �� ����� �����, � ���� ������ �� ����� ������� ��� ����� ������� "��������"
			break;
		}
	}
	return false;
}

void Player::check() 
{
	int last_act = game -> lastAction;
	/*
		���� ��������� ��������� ��� �������, 
			���� ������� �������� ��� ������,
			�� ����� ���������� ���
	*/
	if(last_act == ACTION_CHECKED
	/*|| last_act == ACTION_NONE*/) game -> dealNextCards = true;//ACTION_NONE ������, ������ ��� ����� ������ ����� ������� ������� ����� ������ ������ ��� ����� ������ �����
	
	game -> writeToHistory(" ��������� ���.");

	game -> lastAction = ACTION_CHECKED;
}

void Player::call() 
{
	int last_act = game -> lastAction;
	/*
		���� ������� �� ����������� call �� ������� ������ ����� � ������
		���� ����� �� �������, �� ������ all in � ����� ������� 5 ���� �� ����
	*/
	if(last_act == ACTION_RAISED
	|| last_act == ACTION_ALLIN) 
	{
		if(money > table -> last_bet)//���� ������� ����� ��� ����������� - � ������ (������ ���� ����� ����� ���������� �������� � �����)
		{
			game -> dealNextCards = true;//����� ��������� ��������� �����
			money -= table -> last_bet; //������� ������ ��� ������������� ������

			table -> to_TableBank(table -> last_bet);

			string s_temp = "������� ������, �������� " + to_string( long long(table -> last_bet) ) + "$";
			game -> writeToHistory(s_temp);
			
			if(last_act == ACTION_ALLIN) game -> startStageRiver();//���� �������� ����� ��� ��, � ��� ������� ����� ��� �� ������ ��������, �� �������� ��������� ������ ����

			last_act = ACTION_CALLED;
		}
		else//���� �� ������� ����� ��� �����������, �� �� ������ ������ "�� ��"
		{
			allin();

			game -> lastAction = ACTION_ALLIN;
		}
	}
}
	
void Player::fold() {
	/*
		������� ��������� � ������ ���� ������ �� �������
		������ ������ �� ����� ���������� ������
		������ ����� ��������� � ����� FinishGame, ��� ��������
			���� ������ ������ �� ������� ����������� - ���� �������������
			���� ������ ��������, �� �������� ����� ������
	*/
	
	string s_temp = "������� �����, ����� ���������� ��� � " + to_string( long long(table -> table_money)) + "$";
	game -> writeToHistory(s_temp);

	//������ ������� ���� ����� ����������
	if(game -> activePlayer == PLAYER_COMPUTER) game -> rewardGameWinner(PLAYER_USER);
	else if(game -> activePlayer == PLAYER_USER) game -> rewardGameWinner(PLAYER_COMPUTER);
	
	
	game -> lastAction = ACTION_FOLD;

	//������ ����� ��������� ���������� � FinishGame (������ ����� ���������� ���� ���������)
	if(game -> activePlayer == PLAYER_COMPUTER) game -> FinishGame(PLAYER_USER);
	else if(game -> activePlayer == PLAYER_USER) game -> FinishGame(PLAYER_COMPUTER);
}

void Player::raise(int sum) 
{
	int last_act = game -> lastAction;

	//int sum = 0;
	
	bool bad_key = false; //������ �������� �������

	do//���������� �������, ���� �� ������ ������
	{
		if(sum == 0)//����� ��������� �����, - ���������� ����� ==0, ����� ��������� - ����� ������� ��������
		{
			cout << "������� ����� ����� ��� �������� ������: ";
			cin >> sum;
		}

		if(sum <= 0) bad_key = true;//���� ���� �������� ��������
		if( (table -> last_bet) + sum < money)//���� ������� ����� ��� �� ������� ������� �������� � ����������� �������
		{
			money -= (table -> last_bet) + sum;//������� ��� ����� �������, �� ������� �������� �������� + ������� �������� 
			
			table -> to_TableBank( (table -> last_bet) + sum);
			
			string s_temp = "������ ������, �������� " + to_string( long long((table -> last_bet) + sum) ) + "$";
			game -> writeToHistory(s_temp);

			table -> last_bet = sum;//��������� ������� ����� ������� ��������

			game -> lastAction = ACTION_RAISED;
		}
		else if( (table -> last_bet) + sum >= money)//���� �� �������� ������� �� ����� ������� ����� ������ ��� �� ��� ��� ������, �� �� ������ All-In
		{
			allin();
		}
	}
	while(bad_key == true);
}

void Player::allin() 
{		
	table -> to_TableBank(money);
			
	table -> last_bet = money;//��������� ������� ����� ������� ��������

	string s_temp = "�������� �� ��� ��� ������, � ����� " + to_string( long long(money) ) + "$";
	money = 0;
	game -> writeToHistory(s_temp);

	//game -> dealNextCards = true;

	if(game -> lastAction == ACTION_ALLIN) game -> startStageRiver(); //���� �������� ����� ���� �����

	game -> lastAction = ACTION_ALLIN;
	//� ���� ������ ����� ������ �����������, ��� ����� ����
}

