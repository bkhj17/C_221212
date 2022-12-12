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
	public:		//���������� public
		Monster();	//������
		Monster(string n, int h, int a);
		~Monster(); //�Ҹ���

		void InputMonsterInfo();
		void ShowInfo();

		static void ShowMonsterCount();
	private:	//���������� private
		//��� ���� : Ŭ���� ���ο��� ������ ����
		static int monsterCount;
		//����ü�� ���������� �е� ��
		int attack = 0;
		int hp = 0;
		string name;
	};
public:
	// Base��(��) ���� ��ӵ�
	virtual void Run() override;
};