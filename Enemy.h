#pragma once

class Enemy
{
public:

    void Update();

    void Draw();

public:

    float x = 0;

    float z = 1000;

    bool alive = true;

    int hp = 3;
};
