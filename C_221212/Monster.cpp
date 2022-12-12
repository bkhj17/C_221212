#include "Monster.h"
#include <iostream>
#include "UsefulFunc.h"

const string Monster::DEFAULT_NAME = string("°íºí¸°");

Monster::Monster()
{
	SetData();
}

void Monster::SetData()
{
	Character::SetData(Monster::DEFAULT_NAME,
		MakeRandByRange(Monster::DEFAULT_HP - 1, Monster::DEFAULT_HP + 1), 
		MakeRandByRange(Monster::DEFAULT_ATTACK - 1, Monster::DEFAULT_ATTACK + 1),
		MakeRandByRange(Monster::DEFAULT_DEFENCE - 1, Monster::DEFAULT_DEFENCE + 1));
	this->dropExp = MakeRandByRange(Monster::DEFAULT_EXP - 1, Monster::DEFAULT_EXP + 1);
	if (this->dropExp <= 0)
		this->dropExp = 1;
}
void Monster::ShowInfo()
{
	cout << name << endl
		<< "HP : " << curHp << " / " << maxHp << endl
		<< "ATK : " << attack << endl
		<< "DEF : " << defence << endl << endl;
}

void Monster::ShowShortInfo()
{
	cout << name << "HP(" << curHp << "/" << maxHp << ") ATK : " << attack << " DEF : " << defence << "\n";
}

int Monster::Attacked(int attack)
{
	return DefaultAttacked(attack);
}
