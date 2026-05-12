#include "HitEffect.h"

#include "Projection.h"

#include <graphics.h>

void HitEffect::Update()
{
    life--;

    if (life <= 0)
    {
        alive = false;
    }
}

void HitEffect::Draw()
{
    ProjectionResult p =
        Projection::Project(x, z);

    int r = life * 2;

    if (r < 2)
    {
        r = 2;
    }

    // 外圈

    setfillcolor(color);

    solidcircle(
        p.screenX,
        p.screenY,
        r
    );

    // 内核

    setfillcolor(WHITE);

    solidcircle(
        p.screenX,
        p.screenY,
        r / 2
    );
}