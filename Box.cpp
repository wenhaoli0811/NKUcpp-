#include "Box.h"

#include "Projection.h"

#include <graphics.h>
#include <easyx.h>

#include <windows.h>
#pragma comment(lib, "Msimg32.lib")

// 宝箱贴图
IMAGE boxImg;

bool boxImgLoaded = false;

void Box::Update()
{
    z -= 2;

    if (z < 0)
    {
        alive = false;
    }
}

void Box::Draw()
{
    ProjectionResult p =
        Projection::Project(x, z);

    int size =
        (int)(200 * p.scale);

    if (size < 24)
    {
        size = 24;
    }

    // 加载PNG
    if (!boxImgLoaded)
    {
        loadimage(
            &boxImg,
            L"Box.png",
            128,
            128,
            true
        );

        boxImgLoaded = true;
    }

    // PNG透明绘制
    BLENDFUNCTION blend = {
        AC_SRC_OVER,
        0,
        255,
        AC_SRC_ALPHA
    };

    AlphaBlend(
        GetImageHDC(NULL),      // 目标
        p.screenX - size / 2,
        p.screenY - size / 2,
        size,
        size,

        GetImageHDC(&boxImg),   // 源
        0,
        0,
        128,
        128,

        blend
    );
}