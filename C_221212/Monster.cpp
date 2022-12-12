#include "Monster.h"
#include <iostream>

Monster::Monster(string name, int maxHp, int attack, int defence, int dropExp)
	: Character(name, maxHp, attack, defence), dropExp(dropExp)
{
}

void Monster::SetData(string name, int maxHp, int attack, int defence, int dropExp)
{
	Character::SetData(name, maxHp, attack, defence);
	this->dropExp = dropExp;
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
	cout << name << "HP(" << curHp << "/" << maxHp << ")\n";
}
