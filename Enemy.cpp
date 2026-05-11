#include "Enemy.h"

#include "Projection.h"

#include <graphics.h>

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
        (int)(90 * p.scale);

    if (size < 18)
    {
        size = 18;
    }

    // =========================
    // 直接绘制PNG
    // =========================

// =========================
// 绘制敌人
// =========================

    putimage(
        p.screenX - 64,
        p.screenY - 64,
        &enemyImg
    );
    
}