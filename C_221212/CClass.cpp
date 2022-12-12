#include "CClass.h"
#include <iostream>

//Ŭ���� ���� static ������ Ŭ���� �ܺο��� �ʱ�ȭ ��ų��(����� �� �˷��ش�)
//�ڷ��� Ŭ�����̸�::�����̸� = �ʱⰪ
int CClass::Monster::monsterCount = 5;

void CClass::Run()
{
	/*
	Monster monster;	
	monster.InputMonsterInfo();
	monster.ShowInfo();
	*/

	//new : Heap�� �Ҵ��ϰ� �Ҵ�� �޸��� �����ּҸ� ��ȯ
	Monster* monster = new Monster("Orc", 50, 15);
	//monster->InputMonsterInfo();
	monster->ShowInfo();

	cout << "monster �ּ� : " << monster << "\n";
	delete monster;	
	//monster->InputMonsterInfo(); �Ҵ� �� �ƴµ� �����Ϸ� �ϸ� ������

	int count = 0;
	cout << "�Ҵ��� ���� ���� : ";
	cin >> count;
	//int arr[���]
	Monster* monsters = new Monster[count];

	delete[] monsters;
}

CClass::Monster::Monster()
{
	cout << "���� ������ ȣ��\n";
	++monsterCount;
}

CClass::Monster::Monster(string name, int hp, int attack)
	: name(name), hp(hp), attack(attack)
{
	cout << "this : " << this << "\n";
}

CClass::Monster::~Monster()
{
	cout << "���� �Ҹ��� ȣ��\n";
	monsterCount--;
}

void CClass::Monster::InputMonsterInfo()
{
	cout << "���� ���� �Է�\n";
	cout << "Name : ";
	cin >> name;
	cout << "HP : ";
	cin >> hp;
	cout << "Attack : ";
	cin >> attack;
}

void CClass::Monster::ShowInfo()
{
	cout << name << " : HP " << hp << " ATK" << attack << "\n";
}

void CClass::Monster::ShowMonsterCount()
{
	cout << "monsterCount :" << monsterCount << "\n";
}
