#include "Box.h"

#include "Projection.h"

#include <graphics.h>
#include <easyx.h>

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
        (int)(90 * p.scale);

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

    // 绘制PNG

    putimage(
        p.screenX - 64,
        p.screenY - 64,
        &boxImg
    );
}