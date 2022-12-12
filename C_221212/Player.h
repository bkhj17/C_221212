#pragma once
#include "Character.h"

class Player : public Character {
public:
    Player(string name, int level = 1, int exp = 0, int maxHp = 5, int maxMp = 3, int attack = 3, int defence = 1);
    //
    void GainExp(int expGain);
    void LevelUp();

    // Character을(를) 통해 상속됨
    virtual void ShowInfo() override;
    virtual void ShowShortInfo() override;
    virtual int Attacked(int attack) override;
    virtual void TurnEnd() override;

    bool guard = false;
    
    int ReflectSkill();
    string GetData();

private:
    static const int MAX_LEVEL = 5;
    static const int EXP_TABLE[MAX_LEVEL + 1];

    int level = 0;
    int exp;
    int curMp, maxMp;
    bool reflect = false;


};