#include "Player.h"
#include <iostream>
#include <Windows.h>

const int Player::EXP_TABLE[MAX_LEVEL + 1] = { 0, 0, 1, 3, 7, -1 };

Player::Player(string name, int level, int exp, int maxHp, int maxMp, int attack, int defence)
	: Character(name, maxHp, attack, defence), level(level), exp(exp), maxMp(maxMp), curMp(maxMp)
{
}

void Player::GainExp(int expGain)
{
	exp += expGain;
	cout << name << "은/는 " << expGain << "경험치를 얻었다\n";
	Sleep(500);

	while (EXP_TABLE[level + 1] > 0 && exp >= EXP_TABLE[level + 1])
		LevelUp();

}

void Player::LevelUp()
{

	level++;
	maxHp += 5;
	curHp = maxHp;
	maxMp += 1;
	curMp = maxMp;
	attack += 3;
	defence += 3;

	cout << name << "의 레벨이 " << level << "이 되었다!\n";
	ShowInfo();
}

void Player::ShowInfo()
{
	cout << "플레이어 : " << name << endl
		<< "Level : " << level << " ( " << exp << " / " << EXP_TABLE[level + 1] << " )" << endl
		<< "HP : " << curHp << " / " << maxHp << endl
		<< "MP : " << curMp << " / " << maxMp << endl
		<< "ATK : " << attack << endl
		<< "DEF : " << defence << endl << endl;
}

void Player::ShowShortInfo()
{
	cout << name << "HP(" << curHp << "/" << maxHp << ") MP(" << curMp << "/" << maxMp << ")\n";
}

int Player::Attacked(int attack)
{
	if (reflect) {
		cout << name << "은/는 적의 공격을 반사했다!\n";
		return -attack;
	}
	else if (guard) {
		return Damaged(defence * 2 < attack ? attack - defence * 2 : 0);
	}
	else {
		return this->Character::Attacked(attack);
	}
}

string Player::GetData()
{
	string s;
	s += name + " "
		+ to_string(level) + " "
		+ to_string(exp) + " "
		+ to_string(maxHp) + " "
		+ to_string(maxMp) + " "
		+ to_string(attack) + " "
		+ to_string(defence) + " ";
	return s;
}

void Player::TurnEnd()
{
	reflect = guard = false;
}
