#pragma once

#include "Player.h"

class Game
{
public:

    void Init();

    void Run();

    void Update();

    void Render();

private:

    bool running = true;

    Player player;
};