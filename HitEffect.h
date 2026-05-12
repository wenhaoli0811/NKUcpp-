#pragma once
#include <windows.h>
class HitEffect
{
public:
    float x = 0;
    float z = 0;

    int life = 12;

    COLORREF color = RGB(255, 180, 40);
    bool alive = true;

public:
    void Update();
    void Draw();
};
