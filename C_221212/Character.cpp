#include "Character.h"
#include <iostream>
#include <Windows.h>

Character::Character(string name, int maxHp, int attack, int defence)
	: name(name), curHp(maxHp), maxHp(maxHp), attack(attack), defence(defence)
{
}

Character::~Character()
{
}

void Character::SetData(string name, int maxHp, int attack, int defence)
{
	this->name = name;
	this->curHp = this->maxHp = maxHp;
	this->attack = attack;
	this->defence = defence;
}

void Character::Attack(Character* enemy)
{
	cout << name << "은/는 " << enemy->name << "을 공격했다!\n";
	Sleep(500);

	int result = enemy->Attacked(attack);
	if (result < 0) //반사
		Damaged(attack);
}

int Character::DefaultAttacked(int attack)
{
	int damage = (attack > defence) ? attack - defence : 1;
	Damaged(damage);
	return 0;
}

int Character::Damaged(int damage)
{
	curHp -= damage;

	cout << name << "은/는 " << damage << "의 데미지를 입었다.\n";
	Sleep(500);
	return damage;
}

bool Character::IsDead()
{
	return curHp <= 0;
}