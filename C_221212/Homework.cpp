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

	return player != nullptr;
}

void Homework::NewGame() {


	string s;
	system("cls");
	cout << "[새 게임]\n" << "플레이어의 이름을 입력하시오 -> ";
	cin >> s;

	player = new Player(s);
	SaveData();
	player->ShowInfo();
	cout << "계속 하려면 아무 키나 누르시오.";
	while (!_kbhit()) {

	}

}

void Homework::Setting()
{
	int input;
	cout << "1. 불러오기 2. 새 게임 3. 종료 -> ";
	cin >> input;
	switch (input) {
	case 1:
		if (LoadData())
			break;
		cout << "파일을 불러오는 데에 실패하였습니다. \n";
	case 2:
		cout << "새 게임을 시작합니다.\n";
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
		cout << "전투에 나올 몬스터의 수를 입력하시오(1~" << MAX_ENEMY << ", 0은 돌아가기)-> ";
		cin >> input;

		if (input > MAX_ENEMY)
			cout << "너무 많은 수를 부르셨어요. 다시\n";
		else if (input < 0)
			cout << "인간적으로 음수는 아니지. 다시\n";
		else
			break;
	}
	return input;
}
Homework::GameState Homework::SelectMenu() {
	int input = 0;
	system("cls");
	cout << "메뉴 선택\n1. 전투\n2. 저장\n3. 종료\n-> ";
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
		cout << "파일을 여는 데에 실패했습니다. 메뉴로 돌아갑니다.\n";
		return;
	}

	file << player->GetData();
	file.close();
}

void Homework::SetMonsters(int nEnemy)
{
	this->nEnemy = nEnemy;
	while (monsters.size() < nEnemy) {
		monsters.push_back({ true, new Monster() });
	}

}

void Homework::TurnStart()
{
	cout << "====================================\n";
	player->ShowShortInfo();
	for(auto monster : monsters)
		if(monster.first)
			monster.second->ShowShortInfo();
	cout << "====================================\n";
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
			int nEnemy = InputEnemyNum();
			if (nEnemy == 0)
				gameState = GameState::SELECT_MENU;
			else {
				SetMonsters(nEnemy);
				gameState = GameState::TURN_START;
			}
		}
			break;
		case Homework::GameState::TURN_START:
			TurnStart();
			gameState = GameState::SELECT_COMMAND;
			break;
		case Homework::GameState::SELECT_COMMAND:
			break;
		case Homework::GameState::FIGHT:
			break;
		case Homework::GameState::BATTLE_END:
			break;
		case Homework::GameState::GAME_OVER:
			cout << "플레이어 사망.... Game Over" << endl;
			gameState = GameState::SETTING;
			break;
		case Homework::GameState::EXIT:
			exit = true;
			break;
		default:
			break;
		}
	}
	/*
	while (!player->IsDead() && !monster->IsDead()) {

		player->Attack(monster);
		if (monster->IsDead()) {
			player->GainExp(monster->GetDropExp());
			break;
		}

		monster->Attack(player);
		if (player->IsDead()) {
		}
	}
	*/
	for (int i = 0; i < monsters.size(); i++)
		if(monsters[i].second) delete monsters[i].second;
	if(player) delete player;
}
