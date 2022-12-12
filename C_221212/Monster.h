#pragma once
#include "Character.h"

class Monster : public Character {
public:
    static const string DEFAULT_NAME;
    static const int DEFAULT_HP = 5;
    static const int DEFAULT_ATTACK = 2;
    static const int DEFAULT_DEFENCE = 1;
    static const int DEFAULT_EXP = 1;

    Monster();

    void SetData();

    // Character을(를) 통해 상속됨
    virtual void ShowInfo() override;
    virtual void ShowShortInfo() override;

    int GetDropExp() { return dropExp; }
    static const int MAX_MONSTERS = 10;
private:
    int dropExp;

    // Character을(를) 통해 상속됨
    virtual void TurnEnd() override {};

    // Character을(를) 통해 상속됨
    virtual int Attacked(int attack) override;
};
