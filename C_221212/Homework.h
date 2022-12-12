#pragma once
#include "Base.h"
#include "Player.h"
#include "Monster.h"
#include <vector>
using namespace std;

class Homework : public Base
{
private:
    static const string FILE_NAME;
    static const int MAX_ENEMY = 10;

    enum class GameState {
        SETTING,
        SELECT_MENU,
        SAVE_DATA,
        INPUT_ENEMY_NUM,
        TURN_START,
        SELECT_COMMAND,
        FIGHT,
        BATTLE_END,
        GAME_OVER,
        EXIT
    };
    GameState gameState = GameState::SETTING;

    bool LoadData();
    void NewGame();
    void Setting();
    GameState SelectMenu();
    void SetMonsters(int nEnemy);

    void SaveData();
    int InputEnemyNum();
    void TurnStart();

    Player* player = nullptr;

    int nEnemy;
    vector<pair<bool, Monster*>> monsters;
public:
    // Base을(를) 통해 상속됨
    virtual void Run() override;
};

