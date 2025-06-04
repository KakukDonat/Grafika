#include "utils.h"

#include <math.h>

double degree_to_radian(double degree)
{
	return degree * M_PI / 180.0;
}

void set_vec3(vec3* v, float x, float y, float z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

float length(const vec3* v)
{
    return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

vec3 normalized(const vec3* v)
{ 
    float len = length(v);
    return (vec3){v->x / len, v->y / len, v->z / len};
}

vec3 add(const vec3* v1, const vec3* v2)
{
    return (vec3){v1->x + v2->x, v1->y + v2->y, v1->z + v2->z};
}

vec3 subtract(const vec3* v1, const vec3* v2)
{
    return (vec3){v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
}

vec3 multiply(const vec3* v, float scalar)
{
    return (vec3){v->x * scalar, v->y * scalar, v->z * scalar};
}