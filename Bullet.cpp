#include "Bullet.h"

#include <graphics.h>

void Bullet::Update()
{
    // 子弹向远方飞

    z += 20;

    // 飞太远删除

    if (z > 1000)
    {
        alive = false;
    }
}

void Bullet::Draw()
{
    const int screenW = 900;
    const int screenH = 900;

    // 透视比例

    float scale =
        1.0f - z / 1000.0f;

    if (scale < 0.1f)
    {
        scale = 0.1f;
    }

    // 越远越靠中间

    int screenX =
        screenW / 2 + (int)(x * scale);

    // 越远越靠上

    int screenY =
        screenH - 180 - (int)z;

    // 子弹大小

    int size =
        (int)(12 * scale);

    setfillcolor(YELLOW);

    solidcircle(
        screenX,
        screenY,
        size
    );
}