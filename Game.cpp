#include "Game.h"

#include <ctime>
#include <graphics.h>

// 背景图
IMAGE bgImg;

// 是否加载完成
bool bgLoaded = false;

Game::Game()
{
    srand((unsigned int)time(0));
}

void Game::Init()
{
    // 统一窗口大小
    initgraph(900, 900);

    // 加载背景PNG
    loadimage(
        &bgImg,
        L"Background.png",
        900,
        900,
        true
    );

    bgLoaded = true;

    BeginBatchDraw();
}

void Game::Run()
{
    while (true)
    {
        // 更新玩家
        player.Update();

        // 清屏
        cleardevice();

        // 绘制背景
        if (bgLoaded)
        {
            putimage(
                0,
                0,
                &bgImg
            );
        }

        // 绘制道路
        renderer.DrawRoad();

        // 绘制玩家和所有对象
        player.Draw();

        FlushBatchDraw();

        Sleep(16);
    }
}