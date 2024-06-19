/*
 * Made by weld. Github : @atomicwelding.
 */


#include <raylib.h>
#include <raymath.h>
#include <math.h>


#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define TITLE "Central force problem"
#define FPS 60

#define timestep 10000
#define dt (1.0f / FPS)

#define G 1000.0f

typedef struct body {
    const float mass;

    Vector2 position;
    Vector2 velocity;
    
    const float radius;
    const Color color;
} body;

#define CENTER (Vector2){SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f}
Vector2 from_center(Vector2 v) { return Vector2Add(CENTER, v); }

int main(void) {
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(FPS);
    
    body one = {.mass = 1000, .radius = 50.0f, .color = YELLOW}; // massive body
    one.position = from_center((Vector2) {0,0});


    float initial_distance = one.radius + 150.0f;
    body two = {.mass = 0.01, .radius = 5.0f, .color = BLUE}; // small body
    two.position = from_center((Vector2) {initial_distance, 0}); 
    two.velocity = (Vector2) {0, sqrt(G * one.mass / initial_distance)};

    
    Camera2D camera = {};
    camera.target = CENTER;
    camera.offset = (Vector2) {SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    while(!WindowShouldClose()) {

        // handling inputs
        if(IsKeyPressed(KEY_P)) camera.zoom += 0.2f;
        if(IsKeyPressed(KEY_O)) camera.zoom -= 0.2f;
        
        // computing

        Vector2 vec_r = Vector2Subtract(one.position, two.position);
        float r = Vector2Length(vec_r);
        
        Vector2 force = Vector2Scale(Vector2Normalize(vec_r), G * one.mass * two.mass / powf(r,2));
        Vector2 acceleration = Vector2Scale(force, 1.0f / two.mass);
 
        two.velocity = Vector2Add(two.velocity, Vector2Scale(acceleration, dt));
        two.position = Vector2Add(two.position, Vector2Scale(two.velocity, dt));
        
        // drawing
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        DrawCircleV(one.position, one.radius, one.color);
        DrawCircleV(two.position, two.radius, two.color);
        EndMode2D();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
        
