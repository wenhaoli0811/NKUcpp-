#pragma once

struct ProjectionResult
{
    int screenX;

    int screenY;

    float scale;
};

class Projection
{
public:

    static ProjectionResult Project(
        float x,
        float z
    );
};
