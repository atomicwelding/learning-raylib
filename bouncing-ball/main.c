/*
 * Made by weld. Github : @atomicwelding. 
 */


#include <raylib.h>
#include <stdio.h>


// defines
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400
#define TITLE "Bouncing Ball"
#define FPS 60

#define TIMESTEP 10000
#define dt 0.1

#define G 9.8
#define ALPHA 0.05


typedef struct ball {
    Vector2 position;
    Vector2 velocity;
    const Color color;
    const float radius;
} ball;


typedef struct floor {
    const Vector2 startPos;
    const Vector2 endPos;
    const Color color;
} floor;

// utils
Vector2 UsualY(Vector2 v) {
    return (Vector2) { .x = v.x, .y = SCREEN_HEIGHT - v.y};
}


// main
int main(void) {


    ball b = { .position = UsualY( (Vector2) {.x = SCREEN_WIDTH/2, .y = 300}),
               .velocity = (Vector2){0,0},
               .color = RED,
               .radius = 10 };

    floor f = { .startPos = UsualY((Vector2) {0, 10}),
                .endPos   = UsualY((Vector2) {SCREEN_WIDTH, 10}),
                .color = BLACK };
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(FPS);

    unsigned int count = 0;
    while(!WindowShouldClose() && count < TIMESTEP) {
        count += 1;
        
        // computing
        b.velocity.y += (G - b.velocity.y*ALPHA) * dt;
        b.position.y += b.velocity.y * dt;
        
        if(b.position.y + b.radius >= f.startPos.y) {
            b.position.y = f.startPos.y - b.radius;
            b.velocity.y *= -1;
        }
        
        
        // drawing
        BeginDrawing();
        ClearBackground(WHITE);
        DrawLineV(f.startPos, f.endPos, f.color); // ground
        DrawCircleV(b.position, b.radius,  b.color);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
        
