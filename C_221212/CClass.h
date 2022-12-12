#pragma once
#include "Base.h"
#include <string>
using namespace std;

class CClass : public Base
{
	/*
	struct Monster {
		string name;
		int attack = 0;
		int hp = 0;

		void InputMonsterInfo();
		void ShowInfo();
	};
	*/
	class Monster {
	public:		//접근지정자 public
		Monster();	//생성자
		Monster(string n, int h, int a);
		~Monster(); //소멸자

		void InputMonsterInfo();
		void ShowInfo();

		static void ShowMonsterCount();
	private:	//접근지정자 private
		//멤버 변수 : 클래스 내부에서 생성한 변수
		static int monsterCount;
		//구조체와 마찬가지로 패딩 들어감
		int attack = 0;
		int hp = 0;
		string name;
	};
public:
	// Base을(를) 통해 상속됨
	virtual void Run() override;
};