#include "Bullet.h"

#include "Projection.h"

#include <graphics.h>
#include <easyx.h>
#include <windows.h>

#pragma comment(lib, "Msimg32.lib")

// 子弹贴图
IMAGE bulletImg;

bool bulletImgLoaded = false;

void Bullet::Update()
{
    z += 25;

    if (z > 1000)
    {
        alive = false;
    }
}

void Bullet::Draw()
{
    ProjectionResult p =
        Projection::Project(x, z);

    int size =
        (int)(80 * p.scale);

    if (size < 6)
    {
        size = 6;
    }

    // 加载PNG

    if (!bulletImgLoaded)
    {
        loadimage(
            &bulletImg,
            L"Bullet.png",
            32,
            32,
            true
        );

        bulletImgLoaded = true;
    }

    // PNG透明绘制

    BLENDFUNCTION blend =
    {
        AC_SRC_OVER,
        0,
        255,
        AC_SRC_ALPHA
    };

    AlphaBlend(
        GetImageHDC(NULL),
        p.screenX - size / 2,
        p.screenY - size / 2,
        size,
        size,

        GetImageHDC(&bulletImg),
        0,
        0,
        32,
        32,

        blend
    );
}