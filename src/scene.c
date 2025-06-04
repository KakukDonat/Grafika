#include "scene.h"

#include "load.h"
#include "draw.h"
#include <math.h>
#include <stdlib.h>

void random_pos(vec3* vec) {
     float rand_dir = (rand() % 360);
    vec3 forward = new_vec3(cos(degree_to_radian(rand_dir)), sin(degree_to_radian(rand_dir)), 0.0f);
    // 5 to 14
    float distance = (rand() % 15) / 10.0f + 1.5f;
    float rand_x = forward.x * distance;
    float rand_y = forward.y * distance;

    set_vec3(vec, rand_x, rand_y, 1.0f);
    printf("%f %f %f\n", vec->x, vec->y, vec->z);
}

void init_scene(Scene* scene)
{
    scene->rotation = 0.0;
    scene->light = 0.0;
    
	load_model(&(scene->gun), "assets/models/gun.obj");
    scene->texture_id = load_texture("assets/textures/gun.jpg");

    load_model(&(scene->building), "assets/models/ter.obj");
    scene->texture_building = load_texture("assets/textures/ter.jpg");

    load_model(&(scene->help.MoveKey), "assets/models/help.obj");
	scene->texture_key = load_texture("assets/textures/help.jpg");

    load_model(&(scene->plant), "assets/models/plant.obj");
    scene->texture_plant = load_texture("assets/textures/plant.png");
	

    scene->texture_help = load_texture("assets/textures/help.jpg");

	
    scene->material.ambient.red = 1;
    scene->material.ambient.green = 1;
    scene->material.ambient.blue = 1;

    scene->material.diffuse.red = 1; 
    scene->material.diffuse.green = 1; 
    scene->material.diffuse.blue = 1;

    scene->material.specular.red = 1;
    scene->material.specular.green = 1;
    scene->material.specular.blue = 1;

    scene->material.shininess = 50; 

    set_vec3(&(scene->table_pos), 1.5f, -1.1f, 0.0f);
    random_pos(&(scene->gun_pos  ));
    random_pos(&(scene->plant_pos));

    float fogColor[4] = {0.5f, 0.5f, 0.5f, 0.5f};

    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_START, 1.0f);
    glFogf(GL_FOG_END, 5.0f);
    glFogf(GL_FOG_DENSITY, 0.35f);

}

void set_lighting(const Scene* scene)
{
   float b;
    b = scene->light / 255 ;
    float ambient_light[] = { b, b, b, b };
    float diffuse_light[] = { b, b, b, b };
    float specular_light[] = { b, b, b, b };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    // Candle (building) emits light in all directions
    float light_position[] = { 3.0f, 3.0f, 3.0f, 1.0f }; // Position of the light
    GLfloat light_color[] = { 0.5f, 0.5f, 0.5f, 1.0f };

    // Set light properties
    glLightfv(GL_LIGHT1, GL_POSITION, light_position); // Set the position of the light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color); // Set the color of the light
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_color); // Set the specular color of the light

    glEnable(GL_LIGHT1); // Enable the light source
}



void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene, Camera* camera,double elapsed_time)
{
    scene->help.position.x = camera->position.x;
    scene->help.position.y = camera->position.y;
   
    vec3 poscopy = new_vec3(camera->position.x, camera->position.y, 0);

    vec3* poses[3] = {
        &scene->table_pos,
        &scene->plant_pos,
        &scene->gun_pos
    };

    for (int i = 0; i < 3; i++) {
        vec3 curr = new_vec3(poses[i]->x, poses[i]->y, 0);

        // Check if player is colliding with the collider
        vec3 diff = subtract(&poscopy, &curr);
        float len = length(&diff);

        vec3 norm = normalized(&diff);

        if (len < 0.5f) {
            float inside = 0.5f - len;
            vec3 move = multiply(&norm, inside);
            camera->position = add(&camera->position, &move);
            camera->position.z = 1.0f;
        }
    }

    scene->rotation += 0.5 ;
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting(scene);
    draw_origin();
    draw_building(scene);
    draw_gun(scene);
    draw_plant(scene);
}


void draw_gun(const Scene* scene){
    glPushMatrix();
    glTranslatef(scene->gun_pos.x, scene->gun_pos.y, scene->gun_pos.z);
    glRotatef(90, 1, 0, 0);
    glRotatef(scene->rotation * 0.3f, 0, 1, 0);
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    set_material(&(scene->material));
    draw_model(&(scene->gun));
    glPopMatrix();
}


void draw_plant(const Scene* scene){
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTranslatef(scene->plant_pos.x, scene->plant_pos.y, scene->plant_pos.z);
    glRotatef(90, 1, 0, 0);
    glRotatef(scene->rotation * -0.3f, 0, 1, 0);
    glScalef(0.125, 0.125, 0.125);
    glBindTexture(GL_TEXTURE_2D, scene->texture_plant);
    set_material(&(scene->material));
    draw_model(&(scene->plant));
    glDisable(GL_BLEND);
    glPopMatrix();
}


void draw_building(const Scene* scene){
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.66, 0.66, 0.66);
    set_lighting(scene);
    glBindTexture(GL_TEXTURE_2D, scene->texture_building);
    set_material(&(scene->material));
    draw_model(&(scene->building));
    glPopMatrix();
}

void Key_up(Scene* scene, int a, Camera* camera){
    int c = a;
    if(c == 1){
        scene->help.position.x = camera->position.x;
        scene->help.position.y = camera->position.y;
        scene->help.position.z = camera->position.z;
    }
}

void set_sun_brightness_inc(Scene* scene, float b)
{
   scene->light += b;

    if(scene->light > 255.0){
        scene->light = 255.0;
    }
    if(scene->light < 0.0){
        scene->light = 0.0;
    }
}

void show_help(GLuint help_texture) {
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, help_texture);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3d(-2, 1.5, -3);
        glTexCoord2f(1, 0);
        glVertex3d(2, 1.5, -3);
        glTexCoord2f(1, 1);
        glVertex3d(2, -1.5, -3);
        glTexCoord2f(0, 1);
        glVertex3d(-2, -1.5, -3);
    glEnd();


    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}