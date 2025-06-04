#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "utils.h"

#include "model.h"

typedef struct Help
{
    Model MoveKey;
    GLuint texture_keyid;
    vec3 position;
    vec3 rotation;
} Help;


typedef struct Scene
{
    Model gun;
    Model building;
    Help help;
    Model plant;
    Material material;
    GLuint texture_id;
    GLuint texture_building;
    GLuint texture_key;
    GLuint texture_help;
    GLuint texture_plant;
    float light;
    float rotation;
    bool is_help_visible;
    vec3 gun_pos;
    vec3 plant_pos;
    vec3 table_pos;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(const Scene* scene);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, Camera* camera, double elapsed_time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw a chair.
 */
void draw_gun(const Scene* scene);

void draw_building(const Scene* scene);

void draw_plant(const Scene* scene);

void Key_up(Scene* scene, int a, Camera* camera);

void set_sun_brightness_inc(Scene* scene, float b);

void show_help(GLuint help_texture);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();


#endif /* SCENE_H */
