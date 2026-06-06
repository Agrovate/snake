#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 800

#define ROWS 20
#define COLS 20
#define CELLSIZE 40
#define SPEED 20

void Draw_Grid();
void DrawApple();
void DrawSnake();
void CreateSnake(Vector2 position, Vector2 direction);
void InputSnake();
void UpdateSnake();

typedef struct SnakeNode{
    Vector2 position;
    Vector2 direction;
    struct SnakeNode* next;
}SnakeNode;

SnakeNode* head = NULL;
SnakeNode* tail = NULL;
float timer = 0.0f;

int main(){
    InitWindow(WIDTH, HEIGHT, "Snake Game");
    SetTargetFPS(60);

    Vector2 snake = {10*CELLSIZE,10*CELLSIZE};
    CreateSnake((Vector2){10*CELLSIZE,10*CELLSIZE}, (Vector2){0,0});

    // Controls Snakes movement and Speed
    Vector2 direction = {0, 0};

    while(!WindowShouldClose()) {
        InputSnake();
        UpdateSnake();

        BeginDrawing();

        ClearBackground(BLACK); //Background

        //Grids
        Draw_Grid();

        DrawApple();
        DrawSnake();

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
void InputSnake(){
    SnakeNode* travel = head;
    while(travel != NULL){
        if(IsKeyPressed(KEY_RIGHT)) travel->direction = (Vector2) {1, 0};

        if(IsKeyPressed(KEY_LEFT)) travel->direction = (Vector2) {-1, 0};

        if(IsKeyPressed(KEY_UP)) travel->direction = (Vector2) {0, -1};

        if(IsKeyPressed(KEY_DOWN)) travel->direction = (Vector2) {0, 1};

        travel = travel->next;
    }
}
void UpdateSnake() {
    SnakeNode* travel = head;
    timer += GetFrameTime();
    while(travel != NULL){
        if(timer >= 1.0/SPEED) {
            travel->position.x += travel->direction.x * CELLSIZE;
            travel->position.y += travel->direction.y * CELLSIZE;
        }
        travel = travel->next;
    }
    if(timer >= 1.0/SPEED) timer -= 1.0/SPEED;
}
void DrawSnake(){
    SnakeNode* travel = head;
    while(travel != NULL){
        DrawRectangleV(
                travel->position,
                (Vector2){CELLSIZE - 1, CELLSIZE - 1},
                WHITE
        );
        travel = travel->next;
    }
}

void CreateSnake(Vector2 position, Vector2 direction){
    if(head == NULL) {
        //Create the head node
        head = (SnakeNode*)malloc(sizeof(SnakeNode));

        head->position = position;
        head->direction = direction;
        head->next = NULL;

        tail = head;
    }
    else {
        //Create a new node to attach to head
        SnakeNode* body = (SnakeNode*)malloc(sizeof(SnakeNode));

        body->position = position;
        body->direction = direction;
        body->next = NULL;
        tail->next = body;

        tail = body;
    }
}
