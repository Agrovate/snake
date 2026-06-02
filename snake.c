#include <raylib.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 800

#define ROWS 20
#define COLS 20
#define CELLSIZE 40
#define SPEED 5

void grid();
void apple();

int main(){
    InitWindow(WIDTH, HEIGHT, "Snake Game");
    SetTargetFPS(60);

    Vector2 snake = {10*CELLSIZE,10*CELLSIZE};

    while(!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK); //Background

        //Grids
        grid();

        DrawRectangleV(
                snake,
                (Vector2){CELLSIZE - 1, CELLSIZE - 1},
                BLUE
        );

        if(IsKeyDown(KEY_RIGHT)) snake.x += CELLSIZE;

        if(IsKeyDown(KEY_LEFT)) snake.x -= CELLSIZE;

        if(IsKeyDown(KEY_UP)) snake.y -= CELLSIZE;

        if(IsKeyDown(KEY_DOWN)) snake.y += CELLSIZE;

            DrawText(TextFormat("frame data %d",GetFrameTime()), 200, 200, 20, PINK);

       apple();

        EndDrawing();
    }
    CloseWindow();
}

void grid(){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS;j++) {
            int posX = j*CELLSIZE;
            int posY = i*CELLSIZE;

            DrawRectangleLines(posX, posY, CELLSIZE, CELLSIZE, WHITE);
        }
    }
}

void apple() {
        DrawCircle(
                (0*CELLSIZE+1*CELLSIZE)/2,
                (0*CELLSIZE+1*CELLSIZE)/2,
                (int)((CELLSIZE - 1)/2),
                RED
        );
}
