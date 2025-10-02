#ifndef VEC4_H
#define VEC4_H

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief 
 * Can be used as a RGBA color.
 */
typedef union Vec4
{
    struct 
    {
        float x;
        float y;
        float z;
        float w;
    };
    float data[4];

} Vec4, Vector4;

Vec4 vec4(float x, float y, float z, float w);
Vec4 vec4_add(Vec4 a, Vec4 b);
Vec4 vec4_sub(Vec4 a, Vec4 b);
float vec4_dot(Vec4 a, Vec4 b);
float vec4_length(Vec4 vec);
float vec4_magnitude(Vec4 vec);
Vec4 vec4_normalize(Vec4 vec);
bool vec4_is_equal(Vec4 a, Vec4 b);

#endif