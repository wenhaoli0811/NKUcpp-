#pragma once

#include <vector>

#include "Bullet.h"
#include "Enemy.h"
#include "Box.h"

class Player
{
public:

    void Update();

    void Draw();
    int baseHP = 10;
    bool gameOver = false;
    int wave = 1;
    int waveTimer = 0;
public:

    float x = 0;

    float z = 0;

    // 子弹

    std::vector<Bullet> bullets;

    // 敌人

    std::vector<Enemy> enemies;

    // 宝箱

    std::vector<Box> boxes;

    // 射击计时

    int shootTimer = 0;

    // 射击间隔（越小越快）

    int shootDelay = 10;

    // 敌人生成

    int enemyTimer = 0;

    // 宝箱生成

    int boxTimer = 0;

    // 强化等级

    int powerLevel = 1;
};