#include "Renderer.h"

#include <graphics.h>

void Renderer::DrawRoad()
{
    const int screenW = 900;
    const int screenH = 900;

    const int centerX = screenW / 2;

    const int nearWidth = 700;

    const int farWidth = 80;

    for (int y = 0; y < screenH; y++)
    {
        float t = (float)y / screenH;

        int roadWidth =
            farWidth +
            (nearWidth - farWidth) * t;

        int left =
            centerX - roadWidth / 2;

        int right =
            centerX + roadWidth / 2;

        int gray =
            40 + (int)(30 * t);

        setlinecolor(RGB(gray, gray, gray));

        line(left, y, right, y);

        setlinecolor(WHITE);

        putpixel(left, y, WHITE);

        putpixel(right, y, WHITE);
    }
}