/*
 * Made by weld. Github : @atomicwelding. 
 */


#include <raylib.h>
#include <math.h>
#include <raymath.h> 

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define TITLE "3-body problem. Not stable."
#define FPS 60

#define timestep 10000
#define dt (1.0f/FPS)

typedef struct body {
    const float mass;
    const float radius;

    Vector2 position;
    Vector2 velocity;
    

    const Color color;
} body;

#define G 100000.0f

Vector2 F(body m2, body m1) {
    // Force from m2 acting on m1
    Vector2 direction = Vector2Subtract(m2.position, m1.position);
    float distance  = Vector2Length(direction);

    Vector2 force = Vector2Scale(Vector2Normalize(direction), G * m1.mass * m2.mass / powf(distance, 2));
    return force;
}

#define CENTER (Vector2){SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f}
Vector2 from_center(Vector2 v) { return Vector2Add(CENTER, v); }

int main(void) {
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(FPS);

    Vector2 triangle[3] = {(Vector2) {0,0}, (Vector2) {190.0f,-200.0f}, (Vector2) {195.0f,200.0f}}; 

    body one = {.mass = 1.0f, .radius = 4.0f, .color = RED};
    one.position = triangle[0];
    body two = {.mass = 1.0f, .radius = 4.0f, .color = BLUE};
    two.position = triangle[1];
    body three = {.mass = 1.0f, .radius = 4.0f, .color = GREEN};
    three.position = triangle[2];


    Camera2D camera = {};
    camera.target = CENTER;
    camera.offset = CENTER;
    camera.rotation = 0.0f;
    camera.zoom = 1.0f; 
    
    
    while(!WindowShouldClose()) {
        // computing

        // one
        Vector2 f21 = F(two, one);
        Vector2 f31 = F(three,one);
        Vector2 a1 = Vector2Scale(Vector2Add(f21, f31), 1.0f / one.mass);

        one.velocity = Vector2Add(one.velocity, Vector2Scale(a1, dt));
        one.position = Vector2Add(one.position, Vector2Scale(one.velocity, dt));

        // two
        Vector2 f12 = F(one,two);
        Vector2 f32 = F(three, two);
        Vector2 a2 = Vector2Scale(Vector2Add(f12, f32), 1.0f / two.mass);

        two.velocity = Vector2Add(two.velocity, Vector2Scale(a2, dt));
        two.position = Vector2Add(two.position, Vector2Scale(two.velocity, dt));

        // three
        Vector2 f13 = F(one,three);
        Vector2 f23 = F(two, three);
        Vector2 a3 = Vector2Scale(Vector2Add(f13, f23), 1.0f / three.mass);

        three.velocity = Vector2Add(three.velocity, Vector2Scale(a3, dt));
        three.position = Vector2Add(three.position, Vector2Scale(three.velocity, dt));
        
        
        
        // drawing
        BeginDrawing(); 
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
        DrawCircleV(from_center(one.position), one.radius, one.color);
        DrawCircleV(from_center(two.position), two.radius, two.color);
        DrawCircleV(from_center(three.position), three.radius, three.color);
        EndMode2D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
        
