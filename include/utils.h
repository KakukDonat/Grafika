#ifndef UTILS_H
#define UTILS_H

#define FALSE 0
#define TRUE 1

/**
 * GLSL-like three dimensional vector
 */
typedef struct vec3
{
    float x;
    float y;
    float z;
} vec3;

#define new_vec3(x, y, z) (vec3){x, y, z}

void set_vec3(vec3* v, float x, float y, float z);

/**
 * Color with RGB components
 */
typedef struct Color
{
    float red;
    float green;
    float blue;
    float alpha;
} Color;

/**
 * Material
 */
typedef struct Material
{
    struct Color ambient; 
    struct Color diffuse; 
    struct Color specular; 
    float shininess;
} Material;

/**
 * Calculates radian from degree.
 */
double degree_to_radian(double degree);

float length(const vec3* v);

vec3 normalized(const vec3* v);

vec3 add(const vec3* v1, const vec3* v2);

vec3 subtract(const vec3* v1, const vec3* v2);

vec3 multiply(const vec3* v, float scalar);

#endif /* UTILS_H */
