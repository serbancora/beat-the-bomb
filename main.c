#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "raylib.h"

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

Cell grid[COLS + 1][ROWS + 1];

bool IndexIsValid(int, int);
void CellRevealed(int, int);
int CountMines(int, int);
void check0(int x, int y);
void border();

int main()
{
    int MINESNUMBER;
    InitWindow(screenWidth, screenHeight, "Raylib Template");

// START
    play:
    //  resetare random
    srand(time(0));

    // incarcare textures

    Texture2D bombTexture = LoadTexture("C:\\Users\\Serban\\CLionProjects\\untitled\\beat the bomb\\textures\\bomb.png");
    if (bombTexture.id == 0)
    {
        printf("Failed to load texture!\n");
        CloseWindow();
        return 1;
    }

    Texture2D boxTexture = LoadTexture("C:\\Users\\Serban\\CLionProjects\\untitled\\beat the bomb\\textures\\box.png");
    if (boxTexture.id == 0)
    {
        printf("Failed to load texture!\n");
        CloseWindow();
        return 2;
    }

    Texture2D box0Texture = LoadTexture("C:\\Users\\Serban\\CLionProjects\\untitled\\beat the bomb\\textures\\box0.png");
    if (box0Texture.id == 0)
    {
        printf("Failed to load texture!\n");
        CloseWindow();
        return 3;
    }

    Texture2D box1Texture = LoadTexture("C:\\Users\\Serban\\CLionProjects\\untitled\\beat the bomb\\textures\\box1.png");
    if (box1Texture.id == 0)
    {
        printf("Failed to load texture!\n");
        CloseWindow();
        return 4;
    }

    Texture2D box2Texture = LoadTexture("C:\\Users\\Serban\\CLionProjects\\untitled\\beat the bomb\\textures\\box2.png");
    if (box2Texture.id == 0)
    {
        printf("Failed to load texture!\n");
        CloseWindow();
        return 5;
    }

    Texture2D box3Texture = LoadTexture("C:\\Users\\Serban\\CLionProjects\\untitled\\beat the bomb\\textures\\box3.png");
    if (box3Texture.id == 0)
    {
        printf("Failed to load texture!\n");
        CloseWindow();
        return 6;
    }

    Texture2D box4Texture = LoadTexture("C:\\Users\\Serban\\CLionProjects\\untitled\\beat the bomb\\textures\\box4.png");
    if (box4Texture.id == 0)
    {
        printf("Failed to load texture!\n");
        CloseWindow();
        return 7;
    }

    Texture2D box5Texture = LoadTexture("C:\\Users\\Serban\\CLionProjects\\untitled\\beat the bomb\\textures\\box5.png");
    if (box5Texture.id == 0)
    {
        printf("Failed to load texture!\n");
        CloseWindow();
        return 8;
    }

    Texture2D box6Texture = LoadTexture("C:\\Users\\Serban\\CLionProjects\\untitled\\beat the bomb\\textures\\box6.png");
    if (box6Texture.id == 0)
    {
        printf("Failed to load texture!\n");
        CloseWindow();
        return 9;
    }

    Texture2D box7Texture = LoadTexture("C:\\Users\\Serban\\CLionProjects\\untitled\\beat the bomb\\textures\\box7.png");
    if (box7Texture.id == 0)
    {
        printf("Failed to load texture!\n");
        CloseWindow();
        return 10;
    }

    Texture2D box8Texture = LoadTexture("C:\\Users\\Serban\\CLionProjects\\untitled\\beat the bomb\\textures\\box8.png");
    if (box8Texture.id == 0)
    {
        printf("Failed to load texture!\n");
        CloseWindow();
        return 11;
    }

    Texture2D flagTexture = LoadTexture("C:\\Users\\Serban\\CLionProjects\\untitled\\beat the bomb\\textures\\flag.png");
    if (flagTexture.id == 0)
    {
        printf("Failed to load texture!\n");
        CloseWindow();
        return 12;
    }

    Texture2D bomb = LoadTexture("C:\\Users\\Serban\\CLionProjects\\untitled\\beat the bomb\\textures\\bomb.png");
    if (bomb.id == 0)
    {
        printf("Failed to load texture!\n");
        CloseWindow();
        return 13;
    }
    Texture2D startMenu = LoadTexture("C:\\Users\\Serban\\CLionProjects\\untitled\\beat the bomb\\textures\\startmenu.png");
    if (startMenu.id == 0)
    {
        printf("Failed to load texture!\n");
        CloseWindow();
        return 13;
    }
    Texture2D difficultyMenu = LoadTexture("C:\\Users\\Serban\\CLionProjects\\untitled\\beat the bomb\\textures\\difficulty.png");
    if (difficultyMenu.id == 0)
    {
        printf("Failed to load texture!\n");
        CloseWindow();
        return 13;
    }
    // start menu
    bool start = false;
    bool optionsMenu = false;
    while (start != true)
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (optionsMenu == false)
        {
            ClearBackground(RAYWHITE);
        }
        if (optionsMenu == false)
        {
            DrawTextureEx(startMenu, (Vector2){0, 0}, 0, 0.75f, WHITE);
        }
        // play game
        if (IsKeyPressed(KEY_P) && optionsMenu == false)
        {
            start = true;
            break;
        }
        // quit game
        if (IsKeyPressed(KEY_Q) && optionsMenu == false)
        {
            WindowShouldClose();
            UnloadTexture(boxTexture);
            UnloadTexture(box0Texture);
            UnloadTexture(box1Texture);
            UnloadTexture(box2Texture);
            UnloadTexture(box3Texture);
            UnloadTexture(box4Texture);
            UnloadTexture(box5Texture);
            UnloadTexture(box6Texture);
            UnloadTexture(box7Texture);
            UnloadTexture(box8Texture);
            UnloadTexture(flagTexture);
            UnloadTexture(bombTexture);
            UnloadTexture(startMenu);
            UnloadTexture(difficultyMenu);
            return 0;
        }
        // options menu
        if (IsKeyPressed(KEY_O) || optionsMenu == true)
        {
            optionsMenu = true;
            DrawTextureEx(difficultyMenu, (Vector2){0, 0}, 0, 1.4f, WHITE);
            if (IsKeyPressed(KEY_V))
            {
                MINESNUMBER = 7;
                optionsMenu = false;
            }
            if (IsKeyPressed(KEY_E))
            {
                MINESNUMBER = 10;
                optionsMenu = false;
            }
            if (IsKeyPressed(KEY_N))
            {
                MINESNUMBER = 15;
                optionsMenu = false;
            }
            if (IsKeyPressed(KEY_H))
            {
                MINESNUMBER = 23;
                optionsMenu = false;
            }
            if (IsKeyPressed(KEY_I))
            {
                MINESNUMBER = 30;
                optionsMenu = false;
            }
        }
        EndDrawing();
    }
    // initializare griduri
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
                    .flaged = false};
        }
    }
    // localizare mine
    int placeMines = MINESNUMBER;
    while (placeMines > 0)
    {
        int i = 0;
        int j = 0;
        while (i < 1 || j < 1 || i > COLS || j > ROWS)
        {
            i = (rand() % COLS) + 1;
            j = (rand() % ROWS) + 1;
        }
        if (grid[i][j].Mine == false)
        {
            grid[i][j].Mine = true;
            grid[i][j].adjMines = 1;
            placeMines--;
        }
    }

    // bordare grid
    border();

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
    // jocul propriu zis
    while (!WindowShouldClose())
    {
        // input mouse
        // click casuta
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
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            Vector2 mPos = GetMousePosition();
            int indexX = mPos.x / cellsWidth + 1;
            int indexY = mPos.y / cellsHeight + 1;
            if (IndexIsValid(indexX, indexY) == true && grid[indexX][indexY].flaged == false)
            {
                grid[indexX][indexY].flaged = true;
            }
            else if (IndexIsValid(indexX, indexY) == true && grid[indexX][indexY].flaged == true)
            {
                grid[indexX][indexY].flaged = false;
            }
        }
        // desenarea gridului
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 1; i <= COLS; i++)
        {
            for (int j = 1; j <= ROWS; j++)
            {
                DrawRectangleLines((grid[i][j].x - 1) * cellsWidth, (grid[i][j].y - 1) * cellsHeight, cellsWidth, cellsHeight, BLACK);
                if (grid[i][j].revealed == true)
                {
                    if (grid[i][j].Mine == true)
                    {
                        DrawRectangle((grid[i][j].x - 1) * cellsWidth, (grid[i][j].y - 1) * cellsHeight, cellsWidth, cellsHeight, RED);
                        DrawTextureEx(bombTexture, (Vector2){(grid[i][j].x - 1) * cellsWidth, (grid[i][j].y - 1) * cellsHeight}, 0, 0.07f, WHITE);
                    }
                    if (grid[i][j].Mine == false)
                    {
                        if (grid[i][j].adjMines == 1)
                            DrawTextureEx(box1Texture, (Vector2){(grid[i][j].x - 1) * cellsWidth, (grid[i][j].y - 1) * cellsHeight}, 0, 0.065f, WHITE);

                        if (grid[i][j].adjMines == 2)
                            DrawTextureEx(box2Texture, (Vector2){(grid[i][j].x - 1) * cellsWidth, (grid[i][j].y - 1) * cellsHeight}, 0, 0.075f, WHITE);

                        if (grid[i][j].adjMines == 3)
                            DrawTextureEx(box3Texture, (Vector2){(grid[i][j].x - 1) * cellsWidth, (grid[i][j].y - 1) * cellsHeight}, 0, 0.066f, WHITE);

                        if (grid[i][j].adjMines == 4)
                            DrawTextureEx(box4Texture, (Vector2){(grid[i][j].x - 1) * cellsWidth, (grid[i][j].y - 1) * cellsHeight}, 0, 0.066f, WHITE);

                        if (grid[i][j].adjMines == 5)
                            DrawTextureEx(box5Texture, (Vector2){(grid[i][j].x - 1) * cellsWidth, (grid[i][j].y - 1) * cellsHeight}, 0, 0.077f, WHITE);

                        if (grid[i][j].adjMines == 6)
                            DrawTextureEx(box6Texture, (Vector2){(grid[i][j].x - 1) * cellsWidth, (grid[i][j].y - 1) * cellsHeight}, 0, 0.35f, WHITE);

                        if (grid[i][j].adjMines == 7)
                            DrawTextureEx(box7Texture, (Vector2){(grid[i][j].x - 1) * cellsWidth, (grid[i][j].y - 1) * cellsHeight}, 0, 0.077f, WHITE);

                        if (grid[i][j].adjMines == 8)
                            DrawTextureEx(box8Texture, (Vector2){(grid[i][j].x - 1) * cellsWidth, (grid[i][j].y - 1) * cellsHeight}, 0, 0.077f, WHITE);

                        if (grid[i][j].adjMines == 0)
                            DrawTextureEx(box0Texture, (Vector2){(grid[i][j].x - 1) * cellsWidth, (grid[i][j].y - 1) * cellsHeight}, 0, 0.29f, WHITE);
                    }
                }
                if (grid[i][j].revealed == false)
                {
                    DrawTextureEx(boxTexture, (Vector2){((float)(grid[i][j].x - 1)) * cellsWidth, ((float)(grid[i][j].y - 1)) * cellsHeight}, 0, 0.065f, WHITE);
                    if (grid[i][j].flaged == true)
                    {
                        DrawTextureEx(flagTexture, (Vector2){((float)(grid[i][j].x - 1)) * cellsWidth, ((float)(grid[i][j].y - 1)) * cellsHeight}, 0, 0.07f, WHITE);
                    }
                }
            }
        }
        // win/lose check
        int bombs_flagged = 0;
        bool all_revealed = true;
        for (int i = 1; i <= COLS; i++)
        {
            for (int j = 1; j <= ROWS; j++)
            {
                if (grid[i][j].revealed == false)
                {
                    all_revealed = false;
                }
                if (grid[i][j].Mine == true && grid[i][j].flaged == true)
                {
                    bombs_flagged++;
                }
            }
        }
        // lose
        if (all_revealed == true && IsKeyPressed(KEY_K))
        {
            goto play;
        }
        // win
        bool win = false;
        if (bombs_flagged == MINESNUMBER)
        {
            win = true;
        }
        if (win == true && IsKeyPressed(KEY_K))
        {
            goto play;
        }

        EndDrawing();
    }
    // eliberare memorie
    UnloadTexture(boxTexture);
    UnloadTexture(box0Texture);
    UnloadTexture(box1Texture);
    UnloadTexture(box2Texture);
    UnloadTexture(box3Texture);
    UnloadTexture(box4Texture);
    UnloadTexture(box5Texture);
    UnloadTexture(box6Texture);
    UnloadTexture(box7Texture);
    UnloadTexture(box8Texture);
    UnloadTexture(flagTexture);
    UnloadTexture(bombTexture);
    UnloadTexture(startMenu);
    UnloadTexture(difficultyMenu);
    CloseWindow();
    return 0;
}

// verifica daca mouse-ul este pe o celula
bool IndexIsValid(int x, int y)
{
    return x >= 1 && x <= COLS && y >= 1 && y <= ROWS;
}

void CellRevealed(int x, int y)
{
    grid[x][y].revealed = true;

    // lose
    if (grid[x][y].Mine == true)
    {
        for (int i = 1; i <= COLS; i++)
        {
            for (int j = 1; j <= ROWS; j++)
            {
                grid[i][j].revealed = true;
            }
        }
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

// arata toate casutele invecinate cu 0
void check0(int x, int y)
{
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
