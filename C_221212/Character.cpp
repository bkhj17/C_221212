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
	cout << name << "��/�� " << enemy->name << "�� �����ߴ�!\n";
	Sleep(500);

	int result = enemy->Attacked(attack);
	if (result < 0) //�ݻ�
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

	cout << name << "��/�� " << damage << "�� �������� �Ծ���.\n";
	Sleep(500);
	return damage;
}

bool Character::IsDead()
{
	return curHp <= 0;
}