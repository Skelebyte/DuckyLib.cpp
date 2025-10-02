#include "../utils/vec4.h"

Vec4 vec4(float x, float y, float z, float w)
{
    Vec4 vec = {
        x,
        y,
        z,
        w};

    return vec;
}

Vec4 vec4_add(Vec4 a, Vec4 b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;

    return a;
}

Vec4 vec4_sub(Vec4 a, Vec4 b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;

    return a;
}

float vec4_dot(Vec4 a, Vec4 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float vec4_length(Vec4 vec)
{
    return abs(sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w));
}

float vec4_magnitude(Vec4 vec)
{
    return abs(sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w));
}

Vec4 vec4_normalize(Vec4 vec)
{

    Vec4 b = {
        vec.x / vec4_magnitude(vec),
        vec.y / vec4_magnitude(vec),
        vec.z / vec4_magnitude(vec),
        vec.w / vec4_magnitude(vec),
    };

    return b;
}

bool vec4_is_equal(Vec4 a, Vec4 b)
{
    return (a.x == b.x && a.y == b.y && a.z == b.z);
}