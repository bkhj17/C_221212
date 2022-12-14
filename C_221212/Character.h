#pragma once
#include <string>
using namespace std;

class Character {
public:
    Character(string name, int maxHp, int attack, int defence);
    Character() {};
    ~Character();

    void SetData(string name, int maxHp, int attack, int defence);

    virtual void ShowInfo() = 0;
    virtual void ShowShortInfo() = 0;
    void Attack(Character* enemy);
    virtual int Attacked(int attack) = 0;
    int DefaultAttacked(int attack);
    int Damaged(int damage);
    bool IsDead();

    const string& GetName() { return name; };
    virtual void TurnEnd() = 0;
protected:
    int curHp = 10, maxHp = 10, attack = 2, defence = 1;
    string name = "";
};