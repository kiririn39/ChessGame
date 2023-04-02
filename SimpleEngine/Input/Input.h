#pragma once
#include <raylib.h>
#include <map>

class Input
{
public:
    inline static const std::map<int, Vector2> DirectionAxis
    {
        {KEY_A, {-1.0f, 0.0f}},
        {KEY_D, {1.0f, 0.0f}},
        {KEY_LEFT, {-1.0f, 0.0f}},
        {KEY_RIGHT, {1.0f, 0.0f}},

        {KEY_W, {0.0f, -1.0f}},
        {KEY_S, {0.0f, 1.0f}},
        {KEY_UP, {0.0f, -1.0f}},
        {KEY_DOWN, {0.0f, 1.0f}}
    };

    inline static const std::map<int, float> ZoomAxis
    {
        {KEY_Q, 1.0f},
        {KEY_E, -1.0f},
    };

    inline static constexpr int DebugKey = KEY_APOSTROPHE;

    static Vector2 GetVector2AxisInput(const std::map<int, Vector2>& map);
    static float GetFloatAxisInput(const std::map<int, float>& map);
};
