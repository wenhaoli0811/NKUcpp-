#include "Enemy.h"

#include "Projection.h"

#include <graphics.h>
#include <windows.h>

#pragma comment(lib, "Msimg32.lib")

// 敌人图片
IMAGE enemyImg;

bool enemyLoaded = false;

void Enemy::Update()
{
    z -= speed;

    if (z < 30)
    {
        alive = false;
    }
}

void Enemy::Draw()
{
    // =========================
    // 第一次加载图片
    // =========================

    if (!enemyLoaded)
    {
        loadimage(
            &enemyImg,
            L"Enemy.png",
            128,
            128,
            true
        );

        enemyLoaded = true;
    }

    // =========================
    // 透视投影
    // =========================

    ProjectionResult p =
        Projection::Project(x, z);

    // =========================
    // 大小缩放
    // =========================

    int size =
        (int)(240 * p.scale);

    if (size < 18)
    {
        size = 18;
    }

    // =========================
    // 地面阴影
    // =========================

    setfillcolor(RGB(30, 30, 30));

    solidellipse(
        p.screenX - size / 3,
        p.screenY + size / 3,
        p.screenX + size / 3,
        p.screenY + size / 2
    );

    // =========================
    // PNG透明绘制
    // =========================

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

        GetImageHDC(&enemyImg),
        0,
        0,
        128,
        128,

        blend
    );
}