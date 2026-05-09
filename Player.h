#pragma once

#include <vector>

#include "Bullet.h"
#include "Enemy.h"

class Player
{
public:

    void Update();

    void Draw();

public:

    float x = 0;

    float z = 0;

    std::vector<Bullet> bullets;

    std::vector<Enemy> enemies;

    int shootTimer = 0;

    int enemyTimer = 0;
};