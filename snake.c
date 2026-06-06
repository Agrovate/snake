#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 800

#define ROWS 20
#define COLS 20
#define CELLSIZE 40
#define SPEED 10
#define STARTLEN 1

void Draw_Grid();
void DrawApple(int x, int y);
void UpdateApple(int* x, int* y);
void DrawSnake();
void CreateSnake(Vector2 position, Vector2 direction);
void InputSnake();
void UpdateSnake();
void SnakeEats(int x, int y);
void collision();

typedef struct SnakeNode{
    Vector2 position;
    Vector2 direction;
    struct SnakeNode* next;
}SnakeNode;

SnakeNode* head = NULL;
SnakeNode* tail = NULL;
float timer = 0.0f;
bool iseaten = true;
int length = STARTLEN;
bool gameOver = false;

int main(){
    InitWindow(WIDTH, HEIGHT, "Snake Game");
    SetTargetFPS(60);
    srand(time(NULL)^getpid());

    CreateSnake((Vector2){10*CELLSIZE,10*CELLSIZE}, (Vector2){0,0});
    int apple_x,apple_y;

    while(!WindowShouldClose() && !gameOver) {
        UpdateApple(&apple_x, &apple_y);


        InputSnake();
        UpdateSnake();
        SnakeEats(apple_x, apple_y);

        if(length > 0)
            CreateSnake(tail->position, tail->direction);

        BeginDrawing();

        ClearBackground(BLACK); //Background

        //Grids
        Draw_Grid();
        DrawApple(apple_x, apple_y);

        DrawSnake();

        if(head->next != tail)
            collision();

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

void collision() {
    bool collision = false;
    if(head->position.x < 0 || head->position.x > CELLSIZE*(ROWS-1))
        collision = true;
    else if(head->position.y < 0 || head->position.y > CELLSIZE*(COLS-1))
        collision = true;

    SnakeNode* temp = head->next;
    while(temp != NULL){
        if(head->position.x == temp->position.x &&
                (head->position.y == temp->position.y)) {
            collision = true;
            break;
        }
        temp = temp->next;
    }

    if(collision){
        SnakeNode* temp;
        while(head != NULL){
            temp = head->next;
            free(head);
            head = temp;
        }
        tail = NULL;
        gameOver = true;
    }
}

void SnakeEats(int x, int y){
    if(head->position.x == x * CELLSIZE && head->position.y == y * CELLSIZE) {
        iseaten = true;
        length += 1;
    }
}

void UpdateApple(int* x, int* y){
    if(iseaten == true){
        *x = rand()%ROWS;
        *y = rand()%COLS;
        iseaten = false;
    }
}
void DrawApple(int x, int y) {
    DrawCircle(
            (x*CELLSIZE+(x+1)*CELLSIZE)/2,
            (y*CELLSIZE+(y+1)*CELLSIZE)/2,
            (int)((CELLSIZE - 1)/2),
            RED
    );
}
void InputSnake(){
    if(IsKeyPressed(KEY_RIGHT)) head->direction = (Vector2) {1, 0};

    if(IsKeyPressed(KEY_LEFT)) head->direction = (Vector2) {-1, 0};

    if(IsKeyPressed(KEY_UP)) head->direction = (Vector2) {0, -1};

    if(IsKeyPressed(KEY_DOWN)) head->direction = (Vector2) {0, 1};
}
void UpdateSnake() {
    Vector2 prev_pos = head->position;
    Vector2 prev_dir = head->direction;

    timer += GetFrameTime();
    SnakeNode* current = head->next;
    if(timer >= 1.0/SPEED) {
            head->position.x += head->direction.x * CELLSIZE;
            head->position.y += head->direction.y * CELLSIZE;
        while(current != NULL){
            Vector2 temp_pos = current->position;
            Vector2 temp_dir = current->direction;

            current->position = prev_pos;
            current->direction = prev_dir;

            prev_pos = temp_pos;
            prev_dir = temp_dir;

            current = current->next;
        }
        timer -= 1.0/SPEED;
    }
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
    while(length){
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
        length--;
    }
}
