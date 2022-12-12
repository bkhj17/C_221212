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
	int result = enemy->Damaged(attack);
	if (result < 0) //�ݻ�
		Damaged(attack);
}

int Character::Attacked(int attack)
{
	int damage = (attack > defence) ? attack - defence : 1;
	Damaged(damage);
	return damage;
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