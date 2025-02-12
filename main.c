#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "raylib.h"
#include "raymath.h"

#define COLS 10
#define ROWS 10

const int screenWidth = 800;
const int screenHeight = 800;

// auxiliare

const int cellsWidth = screenWidth / (COLS);
const int cellsHeight = screenHeight / (ROWS);

typedef struct Cell
{
    int x;
    int y;
    bool Mine;
    bool revealed;
    bool checked;
    int adjMines;
    bool flaged;
} Cell;

Cell grid[COLS+1][ROWS+1];

void CellDraw(Cell);
bool IndexIsValid(int, int);
void CellRevealed(int, int);
int CountMines(int, int);
void check0(int x, int y);
void border();




int main()
{
    //incarcare poze


    // resetare random

    InitWindow(screenWidth, screenHeight, "Raylib Template");
    play:
    srand(time(0));
    Texture2D boxTexture = LoadTexture("C:\\Users\\Stefan\\CLionProjects\\untitled\\texturi\\box.png");
    if (boxTexture.id == 0)
    {
        // Print an error message if the texture failed to load
        printf("Failed to load texture!\n");
        CloseWindow();
        return 1;
    }
    Texture2D box1Texture = LoadTexture("C:\\Users\\Stefan\\CLionProjects\\untitled\\texturi\\box1.png");
    if (box1Texture.id == 0)
    {
        // Print an error message if the texture failed to load
        printf("Failed to load texture!\n");
        CloseWindow();
        return 1;
    }
    Texture2D box2Texture = LoadTexture("C:\\Users\\Stefan\\CLionProjects\\untitled\\texturi\\box2.png");
    if (box2Texture.id == 0)
    {
        // Print an error message if the texture failed to load
        printf("Failed to load texture!\n");
        CloseWindow();
        return 1;
    }
    Texture2D box3Texture = LoadTexture("C:\\Users\\Stefan\\CLionProjects\\untitled\\texturi\\box3.png");
    if (box3Texture.id == 0)
    {
        // Print an error message if the texture failed to load
        printf("Failed to load texture!\n");
        CloseWindow();
        return 1;
    }
    Texture2D box4Texture = LoadTexture("C:\\Users\\Stefan\\CLionProjects\\untitled\\texturi\\box4.png");
    if (box4Texture.id == 0)
    {
        // Print an error message if the texture failed to load
        printf("Failed to load texture!\n");
        CloseWindow();
        return 1;
    }
    Texture2D box5Texture = LoadTexture("C:\\Users\\Stefan\\CLionProjects\\untitled\\texturi\\box5.png");
    if (box5Texture.id == 0)
    {
        // Print an error message if the texture failed to load
        printf("Failed to load texture!\n");
        CloseWindow();
        return 1;
    }
    Texture2D box6Texture = LoadTexture("C:\\Users\\Stefan\\CLionProjects\\untitled\\texturi\\box6.png");
    if (box6Texture.id == 0)
    {
        // Print an error message if the texture failed to load
        printf("Failed to load texture!\n");
        CloseWindow();
        return 1;
    }
    Texture2D box7Texture = LoadTexture("C:\\Users\\Stefan\\CLionProjects\\untitled\\texturi\\box7.png");
    if (box7Texture.id == 0)
    {
        // Print an error message if the texture failed to load
        printf("Failed to load texture!\n");
        CloseWindow();
        return 1;
    }
    Texture2D box8Texture = LoadTexture("C:\\Users\\Stefan\\CLionProjects\\untitled\\texturi\\box8.png");
    if (box8Texture.id == 0)
    {
        // Print an error message if the texture failed to load
        printf("Failed to load texture!\n");
        CloseWindow();
        return 1;
    }
    /*Texture2D flagTexture = LoadTexture("C:\\Users\\Stefan\\CLionProjects\\untitled\\texturi\\flag.png");
    if (flagTexture.id == 0)
    {
        // Print an error message if the texture failed to load
        printf("Failed to load texture!\n");
        CloseWindow();
        return 1;
    }*/
    Texture2D bomb = LoadTexture("C:\\Users\\Stefan\\CLionProjects\\untitled\\texturi\\bomb.png");
    if (bomb.id == 0)
    {
        // Print an error message if the texture failed to load
        printf("Failed to load texture!\n");
        CloseWindow();
        return 1;
    }

    for (int i = 0; i <= COLS + 1; i++)
    {
        for (int j = 0; j <= ROWS + 1; j++)
        {
            grid[i][j].checked = true;
        }
    }

    for (int i = 1; i <= COLS; i++)
    {
        for (int j = 1; j <= ROWS; j++)
        {
            grid[i][j] = (Cell){
                    .x = i,
                    .y = j,
                    .Mine = false,
                    .revealed = false,
                    .checked = false,
                    .flaged=false};
        }
    }

    // pune mine
    int placeMines = 10;
    while (placeMines > 0)
    {
        int i=0;
        int j=0;
        while (i < 1 || j < 1 || i > COLS || j > ROWS){
            i=(rand()%COLS)+1;
            j=(rand()%ROWS)+1;
        }
        if (grid[i][j].Mine == false)
        {
            grid[i][j].Mine = true;
            grid[i][j].adjMines = 1;
            placeMines--;
        }
    }
    // bordarez grid-ul ca sa nu mai fie probleme la numararea bombelor
    border();
    for(int i=1;i<=10;i++){
        for(int j=1;j<=10;j++){
            printf("%d ",grid[j][i].Mine);
        }
        printf("\n");
    }

    for (int i = 1; i <= COLS; i++)
    {
        for (int j = 1; j <= ROWS; j++)
        {
            if (grid[i][j].Mine == false)
            {
                grid[i][j].adjMines = CountMines(i, j);
            }
        }
    }

    while (!WindowShouldClose())
    {

        // input mouse
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mPos = GetMousePosition();
            int indexX = mPos.x / cellsWidth + 1;
            int indexY = mPos.y / cellsHeight + 1;

            if (IndexIsValid(indexX, indexY) == true)
            {
                check0(indexX, indexY);
                CellRevealed(indexX, indexY);
            }
        }

        // stegulet
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            Vector2 mPos = GetMousePosition();
            int indexX = mPos.x / cellsWidth + 1;
            int indexY= mPos.y /cellsHeight + 1;
            if(IndexIsValid(indexX, indexY)==true && grid[indexX][indexY].flaged==false){
                grid[indexX][indexY].flaged=true;
            }
            else if(IndexIsValid(indexX, indexY)==true && grid[indexX][indexY].flaged==true){
                grid[indexX][indexY].flaged=false;
            }
        }


        // desenez grid-ul
        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (int i = 1; i <= COLS; i++)
        {
            for (int j = 1; j <= ROWS; j++) {

                if(grid[i][j].revealed==false)
                    DrawTextureEx(boxTexture, (Vector2){ ((float)(grid[i][j].x - 1)) * cellsWidth, ((float)(grid[i][j].y - 1)) * cellsHeight},0,0.07f,WHITE);


                else
                {
                    if(grid[i][j].adjMines==1)
                        DrawTextureEx(box1Texture, (Vector2){ (grid[i][j].x-1)*cellsWidth, (grid[i][j].y-1)*cellsHeight},0,0.07f,WHITE);

                    if(grid[i][j].adjMines==2)
                        DrawTextureEx(box2Texture, (Vector2){ (grid[i][j].x-1)*cellsWidth, (grid[i][j].y-1)*cellsHeight},0,0.07f,WHITE);

                    if(grid[i][j].adjMines==3)
                        DrawTextureEx(box3Texture, (Vector2){ (grid[i][j].x-1)*cellsWidth, (grid[i][j].y-1)*cellsHeight},0,0.07f,WHITE);

                    if(grid[i][j].adjMines==4)
                        DrawTextureEx(box4Texture, (Vector2){ (grid[i][j].x-1)*cellsWidth, (grid[i][j].y-1)*cellsHeight},0,0.07f,WHITE);

                    if(grid[i][j].adjMines==5)
                        DrawTextureEx(box5Texture, (Vector2){ (grid[i][j].x-1)*cellsWidth, (grid[i][j].y-1)*cellsHeight},0,0.07f,WHITE);

                    if(grid[i][j].adjMines==6)
                        DrawTextureEx(box6Texture, (Vector2){ (grid[i][j].x-1)*cellsWidth, (grid[i][j].y-1)*cellsHeight},0,0.07f,WHITE);

                    if(grid[i][j].adjMines==7)
                        DrawTextureEx(box7Texture, (Vector2){ (grid[i][j].x-1)*cellsWidth, (grid[i][j].y-1)*cellsHeight},0,0.07f,WHITE);

                    if(grid[i][j].adjMines==8)
                        DrawTextureEx(box8Texture, (Vector2){ (grid[i][j].x-1)*cellsWidth, (grid[i][j].y-1)*cellsHeight},0,0.07f,WHITE);

                    //if(grid[i][j].adjMines==0)
                        //DrawTextureEx(box0Texture, (Vector2){ (grid[i][j].x-1)*cellsWidth, (grid[i][j].y-1)*cellsHeight},0,0.07f,WHITE);



                }



                //CellDraw(grid[i][j]);

            }
        }
        int bombs_flagged=0;
        bool all_revealed=true;
        for(int i=1;i<=COLS;i++){
            for(int j=1;j<=ROWS;j++){
                if(grid[i][j].revealed==false){
                    all_revealed=false;
                }
                if(grid[i][j].Mine==true && grid[i][j].flaged==true){
                    bombs_flagged++;
                }
            }
        }
        //lose
        if(all_revealed==true && IsKeyPressed(KEY_K)){
            goto play;
        }
        //win
        bool win=false;
        if(bombs_flagged==10){
            win=true;
        }
        if(win==true && IsKeyPressed(KEY_K)){
            goto play;
        }
        EndDrawing();
    }
    UnloadTexture(boxTexture);
    CloseWindow();

    return 0;
}

// desenez o celula
void CellDraw(Cell cell)
{
    DrawRectangleLines((cell.x - 1) * cellsWidth, (cell.y - 1) * cellsHeight, cellsWidth, cellsHeight, BLACK);

    if (cell.revealed == true)
    {
        if (cell.Mine == true)
        {
            DrawRectangle((cell.x - 1) * cellsWidth, (cell.y - 1) * cellsHeight, cellsWidth, cellsHeight, RED);
        }

        else
        {
            DrawRectangle((cell.x - 1) * cellsWidth, (cell.y - 1) * cellsHeight, cellsWidth, cellsHeight, LIGHTGRAY);

            if (cell.adjMines != 0)
                DrawText(TextFormat("%d", cell.adjMines), (cell.x - 1) * cellsWidth + 6, (cell.y - 1) * cellsHeight + 4, cellsHeight - 8, BLACK);
                if(cell.adjMines==1){

                }
        }
    }
    else if(cell.flaged==true) {
        DrawRectangle((cell.x - 1) * cellsWidth, (cell.y - 1) * cellsHeight, cellsWidth, cellsHeight, GREEN);
    }
}

// verifica daca mouse-ul este pe o celula
bool IndexIsValid(int x, int y)
{
    return x >= 1 && x <= COLS && y >= 1 && y <= ROWS;
}

void CellRevealed(int x, int y)
{
    grid[x][y].revealed = true;

    if (grid[x][y].Mine == true)
    {
        // lose
        for(int i=1;i<=COLS;i++){
            for(int j=1;j<=ROWS;j++){
                grid[i][j].revealed=true;
            }
        }
    }
    else
    {

        // schimb culoarea celulei

        DrawRectangle(x * cellsWidth, y * cellsHeight, cellsWidth, cellsHeight, LIGHTGRAY);
    }
}

// numara minele vecine
int CountMines(int x, int y)
{
    int count = 0;

    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (IndexIsValid(x, y))
                if (grid[i][j].Mine == true)
                {
                    count++;
                }
        }
    }
    return count;
}

void border() // bordare matrice
{
    for (int i = 0; i <= COLS + 1; i++)
    {
        for (int j = 0; j <= ROWS + 1; j++)
        {
            if (i == 0 || j == 0 || i == COLS + 1 || j == ROWS + 1)
            {
                grid[i][j].Mine = false;
                grid[i][j].adjMines = 1;
            }
        }
    }
}
void check0(int x, int y)
{ // arata toate casutele cu 0
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (grid[i][j].checked == false && grid[i][j].adjMines == 0 && IndexIsValid(i, j))
            {
                grid[i][j].checked = true;
                grid[i][j].revealed = true;
                for (int k = i - 1; k <= i + 1; k++)
                {
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        if (IndexIsValid(k, l))
                            grid[k][l].revealed = true;
                    }
                }

                check0(i, j);
            }
        }
    }
}
