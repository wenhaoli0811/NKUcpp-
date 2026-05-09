#pragma once

class Bullet
{
public:

    void Update();

    void Draw();

public:

    float x = 0;

    float z = 0;

    bool alive = true;
};