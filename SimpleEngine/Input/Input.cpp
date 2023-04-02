#include "Input.h"

#include <raymath.h>

Vector2 Input::GetVector2AxisInput(const std::map<int, Vector2>& map)
{
    Vector2 result{};

    for (std::pair<int, Vector2> keyScale : map)
    {
        if (!IsKeyDown(keyScale.first))
            continue;

        result = Vector2Clamp(Vector2Add(result, keyScale.second), {-1.0f, -1.0f}, {1.0f, 1.0f});
    }

    return result;
}

float Input::GetFloatAxisInput(const std::map<int, float>& map)
{
    float result = 0.0f;

    for (std::pair<int, float> keyScale : map)
    {
        if (IsKeyDown(keyScale.first))
            result = Clamp(result + keyScale.second, -1.0f, 1.0f);
    }

    return result;
}
