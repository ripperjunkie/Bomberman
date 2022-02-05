#include <raylib.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <map>

#define TILE_X 20 
#define TILE_Y 13 
#define TILE_SIZE 40


//Acting as collision filter
enum ECollisionType
{
    BLOCKING,
    OVERLAP
};




int GetTileNumber(int row, int column)
{
    return row * TILE_X - TILE_X + column;
}

void SetPosition(Rectangle& actor, std::vector<Rectangle> tiles, int& row, int& column)
{
    actor.x = tiles[GetTileNumber(row, column)].x;
    actor.y = tiles[GetTileNumber(row, column)].y;
}

bool CollisionCheck()
{
    return true;
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
   
    const int screenWidth = 900;    
    const int screenHeight = 850;

    Rectangle player;
    player.width = TILE_SIZE;
    player.height = TILE_SIZE;
    player.x = 0;
    player.y = 0;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    std::vector<Rectangle> tiles;
    for (int i = 0; i < TILE_X * TILE_Y; i++)
    {
        tiles.push_back(Rectangle());
        tiles[i].width = TILE_SIZE;
        tiles[i].height = TILE_SIZE;
        tiles[i].x = 0;
        tiles[i].y = 0;      
    }

    float store_y = 0.f;
    int posX = 1;
    int posY = 1;

    //place all tiles that holds values
    for (int i = 0; i < tiles.size(); i++)
    {
        if (i != 0)
        {
            tiles[i].x = tiles[i - 1].x + TILE_SIZE + 1.f;
            tiles[i].y = store_y;
        }
        if (i % TILE_X == 0  && i != 0)
        {
            store_y = tiles[i - 1].y + TILE_SIZE + 1.f;
            tiles[i].y = store_y;
            tiles[i].x = 0;
        }
    }
 

    wchar_t wc_level_ = L'CCC';
    char c_collider = 'C';
    char c_player = 'P';
    char c_enemy = 'E';
    char c_item = 'I';

    std::map<int, bool> Tll;
    Tll.emplace(0, true);


    std::string tileNumber  = "0";
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        SetPosition(player, tiles, posY, posX);

        for (size_t i = 0; i < tiles.size(); i++)
        {
            DrawRectangleRec(tiles[i], RED);
            if (i % 2 == 0 && i != 0)
            {
               
                DrawRectangleRec(tiles[i], BLUE);
            }
            if(i ==0)
            {
                DrawRectangleRec(tiles[i], BLUE);
            }
            tileNumber = std::to_string(i);
            DrawText(tileNumber.c_str(), tiles[i].x, tiles[i].y, 20, WHITE);
            
        }

        DrawRectangleRec(player, ORANGE);

        if (IsKeyPressed(KEY_D))
        {
            posX++;
        }
        if (IsKeyPressed(KEY_A))
        {
            posX--;
        }
        if (IsKeyPressed(KEY_W))
        {
            posY--;
        }
        if (IsKeyPressed(KEY_S))
        {
            posY++;
        }

     //   printf("\ntileNumber = %d\n", GetTileNumber(posY, posX));

       // printf("Tile X: %d\nTile Y: %d\n", posX, posY);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

       // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);



        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}