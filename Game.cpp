#include "Game.h"
#include "Renderer.h"

#include <graphics.h>
#include <Windows.h>

Renderer gRenderer;

void Game::Init()
{
    initgraph(900, 900);

    BeginBatchDraw();
}

void Game::Run()
{
    while (running)
    {
        Update();

        Render();

        FlushBatchDraw();

        Sleep(16);
    }

    EndBatchDraw();

    closegraph();
}

void Game::Update()
{
    if (GetAsyncKeyState(VK_ESCAPE))
    {
        running = false;
    }
    player.Update();
}

void Game::Render()
{
    cleardevice();

    gRenderer.DrawRoad();

    player.Draw();
}