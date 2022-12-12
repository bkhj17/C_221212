#pragma once
#include "Character.h"

class Monster : public Character {
public:
    Monster(string name = "고블린", int maxHp = 5, int attack = 2, int defence = 1, int dropExp = 1);

    void SetData(string name, int maxHp, int attack, int defence, int dropExp);

    // Character을(를) 통해 상속됨
    virtual void ShowInfo() override;
    virtual void ShowShortInfo() override;

    int GetDropExp() { return dropExp; }
    static const int MAX_MONSTERS = 10;
private:
    int dropExp;

    // Character을(를) 통해 상속됨
    virtual void TurnEnd() override {};
};
