#include "Enemy.h"

#include <graphics.h>

void Enemy::Update()
{
    // 向玩家推进

    z -= 2;

    // 到达底部

    if (z < 0)
    {
        alive = false;
    }
}

void Enemy::Draw()
{
    const int screenW = 900;
    const int screenH = 900;

    // 透视缩放

    float scale =
        1.0f - z / 1000.0f;

    if (scale < 0.1f)
    {
        scale = 0.1f;
    }

    // 透视位置

    int screenX =
        screenW / 2 + (int)(x * scale);

    int screenY =
        screenH - 180 - (int)z;

    // 敌人大小

    int size =
        (int)(50 * scale);

    // 敌人颜色

    setfillcolor(RED);

    solidrectangle(
        screenX - size,
        screenY - size,
        screenX + size,
        screenY + size
    );
}