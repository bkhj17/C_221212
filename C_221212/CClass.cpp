#include "CClass.h"
#include <iostream>

//클래스 내의 static 변수는 클래스 외부에서 초기화 시킬것(제대로 안 알려준다)
//자료형 클래스이름::변수이름 = 초기값
int CClass::Monster::monsterCount = 5;

void CClass::Run()
{
	/*
	Monster monster;	
	monster.InputMonsterInfo();
	monster.ShowInfo();
	*/

	//new : Heap에 할당하고 할당된 메모리의 시작주소를 반환
	Monster* monster = new Monster("Orc", 50, 15);
	//monster->InputMonsterInfo();
	monster->ShowInfo();

	cout << "monster 주소 : " << monster << "\n";
	delete monster;	
	//monster->InputMonsterInfo(); 할당 안 됐는데 접근하려 하면 터진다

	int count = 0;
	cout << "할당할 몬스터 갯수 : ";
	cin >> count;
	//int arr[상수]
	Monster* monsters = new Monster[count];

	delete[] monsters;
}

CClass::Monster::Monster()
{
	cout << "몬스터 생성자 호출\n";
	++monsterCount;
}

CClass::Monster::Monster(string name, int hp, int attack)
	: name(name), hp(hp), attack(attack)
{
	cout << "this : " << this << "\n";
}

CClass::Monster::~Monster()
{
	cout << "몬스터 소멸자 호출\n";
	monsterCount--;
}

void CClass::Monster::InputMonsterInfo()
{
	cout << "몬스터 정보 입력\n";
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
