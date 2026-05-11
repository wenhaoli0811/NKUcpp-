#include "Projection.h"

ProjectionResult Projection::Project(
    float x,
    float z
)
{
    ProjectionResult result;

    const int screenW = 900;

    const int horizonY = 80;

    const int bottomY = 900;

    const float roadTopWidth = 100.0f;

    const float roadBottomWidth = 660.0f;

    // z: 1000(远) -> 0(近)

    float t =
        1.0f - (z / 1000.0f);

    if (t < 0.0f)
    {
        t = 0.0f;
    }

    if (t > 1.0f)
    {
        t = 1.0f;
    }

    // 道路宽度

    float roadWidth =
        roadTopWidth +
        (roadBottomWidth - roadTopWidth) * t;

    // X投影

    result.screenX =
        screenW / 2 +
        (int)(x * (roadWidth / roadBottomWidth));

    // Y投影

    result.screenY =
        horizonY +
        (int)((bottomY - horizonY) * t);

    // 缩放

    result.scale =
        0.15f + t;

    return result;
}