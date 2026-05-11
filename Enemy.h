#pragma once

class Enemy
{
public:

    void Update();

    void Draw();

public:

    float x = 0;

    float z = 1000;

    float speed = 8;

    int hp = 1;

    bool alive = true;
};