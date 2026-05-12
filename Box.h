#pragma once

class Box
{
public:
    void Update();
    void Draw();

public:
    float x = 300;     // 默认右边
    float z = 1000;    // 远方

    bool alive = true;

    // 宝箱血量
    int hp = 5;
};