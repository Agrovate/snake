#include <raylib.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 800

#define ROWS 20
#define COLS 20
#define CELLSIZE 40
#define SPEED 20

void Draw_Grid();
void DrawApple();

int main(){
    InitWindow(WIDTH, HEIGHT, "Snake Game");
    SetTargetFPS(60);

    Vector2 snake = {10*CELLSIZE,10*CELLSIZE};

    // Controls Snakes movement and Speed
    float timer = 0.0f;
    Vector2 direction = {0, 0};

    while(!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK); //Background

        //Grids
        Draw_Grid();

        DrawRectangleV(
                snake,
                (Vector2){CELLSIZE - 1, CELLSIZE - 1},
                WHITE
        );

        if(IsKeyPressed(KEY_RIGHT)) direction = (Vector2) {1, 0};

        if(IsKeyPressed(KEY_LEFT)) direction = (Vector2) {-1, 0};

        if(IsKeyPressed(KEY_UP)) direction = (Vector2) {0, -1};

        if(IsKeyPressed(KEY_DOWN)) direction = (Vector2) {0, 1};

        timer += GetFrameTime();

        if(timer >= 1.0/SPEED) {
            snake.x += direction.x * CELLSIZE;
            snake.y += direction.y * CELLSIZE;
            timer -= 1.0/SPEED;
        }

       DrawApple();

        EndDrawing();
    }
    CloseWindow();
}

void Draw_Grid(){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS;j++) {
            int posX = j*CELLSIZE;
            int posY = i*CELLSIZE;

            DrawRectangleLines(posX, posY, CELLSIZE, CELLSIZE, WHITE);
        }
    }
}

void DrawApple() {
        DrawCircle(
                (0*CELLSIZE+1*CELLSIZE)/2,
                (0*CELLSIZE+1*CELLSIZE)/2,
                (int)((CELLSIZE - 1)/2),
                RED
        );
}
