#include "Homework.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Monster.h"
#include <conio.h>

const string Homework::FILE_NAME = string("SaveData.txt");

bool Homework::LoadData()
{
	ifstream file;
	file.open(FILE_NAME);
	if (!file)
		return false;
	string name;
	int level, exp, maxHp, maxMp, attack, defence;
	file >> name >> level >> exp >> maxHp >> maxMp >> attack >> defence;
	file.close();

	player = new Player(name, level, exp, maxHp, maxMp, attack, defence);

	player->ShowInfo();
	cout << "��� �Ϸ��� �ƹ� Ű�� �����ÿ�.";
	while (!_kbhit()) {}

	return player != nullptr;
}

void Homework::NewGame() {


	string s;
	system("cls");
	cout << "[�� ����]\n" << "�÷��̾��� �̸��� �Է��Ͻÿ� -> ";
	cin >> s;

	player = new Player(s);
	SaveData();
	player->ShowInfo();
	cout << "��� �Ϸ��� �ƹ� Ű�� �����ÿ�.";
	while (!_kbhit()) {
	}
}

void Homework::Setting()
{
	int input;
	system("cls");
	cout << "1. �ҷ����� 2. �� ���� 3. ���� -> ";
	cin >> input;
	switch (input) {
	case 1:
		if (LoadData())
			break;
		cout << "������ �ҷ����� ���� �����Ͽ����ϴ�. \n";
	case 2:
		cout << "�� ������ �����մϴ�.\n";
		NewGame();
		break;
	default:
		gameState = GameState::EXIT;
		break;
	}
}
int Homework::InputEnemyNum() {
	int input = 0;
	while (1) {
		cout << "������ ���� ������ ���� �Է��Ͻÿ�(1~" << MAX_ENEMY << ", 0�� ���ư���)-> ";
		cin >> input;

		if (input > MAX_ENEMY)
			cout << "�ʹ� ���� ���� �θ��̾��. �ٽ�\n";
		else if (input < 0)
			cout << "�ΰ������� ������ �ƴ���. �ٽ�\n";
		else
			break;
	}
	return input;
}
Homework::GameState Homework::SelectMenu() {
	int input = 0;
	system("cls");
	cout << "�޴� ����\n1. ����\n2. ����\n3. ����\n-> ";
	cin >> input;

	switch (input) {
	case 1:
		return GameState::INPUT_ENEMY_NUM;
	case 2:
		return GameState::SAVE_DATA;
	default:
		return GameState::EXIT;
	}
}

void Homework::SaveData()
{
	ofstream file;
	file.open(FILE_NAME);

	if (!file) {
		cout << "������ ���� ���� �����߽��ϴ�. �޴��� ���ư��ϴ�.\n";
		return;
	}

	player->ShowInfo();
	file << player->GetData();
	file.close();
	cout << "���� �Ϸ�\n";
	cout << "��� �Ϸ��� �ƹ� Ű�� �����ÿ�.";
	while (!_kbhit()) {
	}

}

void Homework::SetMonsters(int numEnemy)
{
	nEnemy = 0;
	for (int i = 0; i < min(monsters.size(), numEnemy); i++) {
		monsters[i]->SetData();
		nEnemy++;
	}

	while (nEnemy < numEnemy) {
		monsters.push_back(new Monster);
		monsters.back()->SetData();
		nEnemy++;
	}
}

void Homework::TurnStart()
{
	system("cls");
	cout << "====================================\n";
	player->ShowShortInfo();
	for(auto monster : monsters)
		if(!monster->IsDead())
			monster->ShowShortInfo();
	cout << "====================================\n";
}

void Homework::Fight()
{
	int input = 0;
	//�÷��̾� �ൿ
	cout << "1. ����\n2. ���\n3. �ݻ�(mp 3)\n4. ����\n-> ";
	cin >> input;

	int curEnemy = nEnemy;
	switch (input) {
	case 1:
		int target;
		cout << "Ÿ�� ����\n";
		for (int i = 0; i < nEnemy; i++) {
			if (monsters[i]->IsDead())
				cout << "X. ";
			else
				cout << i + 1 << ".";
			monsters[i]->ShowShortInfo();
		}

		while (1) {
			cin >> target;
			target--;
			if (target < 0 || target >= nEnemy || monsters[target]->IsDead()) {
				cout << "�߸��� Ÿ���Դϴ�.\n";
				continue;
			}
			break;
		}

		player->Attack(monsters[target]);
		if (monsters[target]->IsDead()) {
			MonsterDead(monsters[target]);
			curEnemy--;
		}
		break;
	case 2:
		player->guard = true;
		break;
	case 3:
		if (!player->ReflectSkill()) {
			cout << "MP ����. �ٽ�\n";
			Sleep(1000);
			return;
		}
		break;
	default:
		cout << "�����ƴ�...";
		while (!_kbhit()) {}
		break;
	}

	if (curEnemy == 0) {
		gameState = GameState::BATTLE_END;
		while (!_kbhit()) {}
		return;
	}

	//���� �ൿ
	for (int i = 0; i < nEnemy; i++) {
		if (monsters[i]->IsDead())
			continue;

		monsters[i]->Attack(player);
		if (player->IsDead()) {
			cout << player->GetName() << "�� �������� ���Ҵ�.\n";
			gameState = GameState::GAME_OVER;
			while (!_kbhit()) {}
			return;
		}

		if (monsters[i]->IsDead()) {
			MonsterDead(monsters[i]);
			curEnemy--;
		}
	}

	if (curEnemy == 0) {
		gameState = GameState::BATTLE_END;
		while (!_kbhit()) {}
		return;
	}

	player->TurnEnd();
	gameState = GameState::TURN_START;
}

void Homework::MonsterDead(Monster* dead)
{
	cout << dead->GetName() << "�� ��������.\n";
	player->GainExp(dead->GetDropExp());
	Sleep(1000);
}

void Homework::Run()
{
	bool exit = false;

	while (!exit) {
		switch (gameState)
		{
		case Homework::GameState::SETTING:
			Setting();
			gameState = GameState::SELECT_MENU;
			break;
		case Homework::GameState::SELECT_MENU:
			gameState = SelectMenu();
			break;
		case Homework::GameState::SAVE_DATA:
			SaveData();
			gameState = GameState::SELECT_MENU;
			break;
		case Homework::GameState::INPUT_ENEMY_NUM:
		{
			int numEnemy = InputEnemyNum();
			if (numEnemy == 0)
				gameState = GameState::SELECT_MENU;
			else {
				SetMonsters(numEnemy);
				gameState = GameState::TURN_START;
			}
		}
			break;
		case Homework::GameState::TURN_START:
			TurnStart();
			gameState = GameState::FIGHT;
			break;
		case Homework::GameState::FIGHT:
			Fight();

			break;
		case Homework::GameState::BATTLE_END:
			cout << "���� ����\n";
			Sleep(1000);
			gameState = GameState::SELECT_MENU;
			break;
		case Homework::GameState::GAME_OVER:
			cout << "�÷��̾� ���.... Game Over\n";
			gameState = GameState::SETTING;
			break;
		case Homework::GameState::EXIT:
			exit = true;
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < monsters.size(); i++)
		if (monsters[i]) delete monsters[i];
	if(player) delete player;
}
