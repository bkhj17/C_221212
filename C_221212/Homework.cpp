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
	cout << "계속 하려면 아무 키나 누르시오.";
	while (!_kbhit()) {}

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
	system("cls");
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

	player->ShowInfo();
	file << player->GetData();
	file.close();
	cout << "저장 완료\n";
	cout << "계속 하려면 아무 키나 누르시오.";
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
	//플레이어 행동
	cout << "1. 공격\n2. 방어\n3. 반사(mp 3)\n4. 도망\n-> ";
	cin >> input;

	int curEnemy = nEnemy;
	switch (input) {
	case 1:
		int target;
		cout << "타겟 선택\n";
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
				cout << "잘못된 타겟입니다.\n";
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
			cout << "MP 부족. 다시\n";
			Sleep(1000);
			return;
		}
		break;
	default:
		cout << "도망쳤다...";
		while (!_kbhit()) {}
		break;
	}

	if (curEnemy == 0) {
		gameState = GameState::BATTLE_END;
		while (!_kbhit()) {}
		return;
	}

	//몬스터 행동
	for (int i = 0; i < nEnemy; i++) {
		if (monsters[i]->IsDead())
			continue;

		monsters[i]->Attack(player);
		if (player->IsDead()) {
			cout << player->GetName() << "는 쓰러지고 말았다.\n";
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
	cout << dead->GetName() << "가 쓰러졌다.\n";
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
			cout << "전투 종료\n";
			Sleep(1000);
			gameState = GameState::SELECT_MENU;
			break;
		case Homework::GameState::GAME_OVER:
			cout << "플레이어 사망.... Game Over\n";
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
