#include "Bullet.h"

#include "Projection.h"

#include <graphics.h>
#include <easyx.h>

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
        (int)(22 * p.scale);

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

    // 绘制PNG

    putimage(
        p.screenX - 16,
        p.screenY - 16,
        &bulletImg
    );
}