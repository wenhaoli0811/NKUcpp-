#pragma once

#include <graphics.h>
#include <vector>

#include "Player.h"
#include "Renderer.h"
#include "Enemy.h"

class Game
{
public:

    // 构造函数
    Game();

    // 初始化
    void Init();

    // 游戏循环
    void Run();

private:

    // 玩家
    Player player;

    // 渲染器
    Renderer renderer;

    // 敌人列表
    std::vector<Enemy> enemies;
};