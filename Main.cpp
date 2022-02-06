#define TILE_X 20 
#define TILE_Y 13 
#define TILE_SIZE 40

#include <raylib.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <map>

#include "TileMap.h"
#include "Entity.h"


//@PARAMS: class, tileMap coordinates
Entity* Spawn()
{
    //TODO
    return NULL;
}





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

    //Rectangle player;
    //player.width = TILE_SIZE;
    //player.height = TILE_SIZE;
    //player.x = 0;
    //player.y = 0;

    int posX = 1;
    int posY = 1;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    std::vector<Rectangle> tiles;
    float store_y = 0.f;
    //std::string tileNumber = "0";

    for (int i = 0; i < TILE_X * TILE_Y; i++)
    {
        tiles.push_back(Rectangle());
        tiles[i].width = TILE_SIZE;
        tiles[i].height = TILE_SIZE;
        tiles[i].x = 0;
        tiles[i].y = 0;      
    }

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
 


    ////Simple and efficient way to setup tile map
    //wchar_t wc_level_ = L'CCC';
    //char c_collider = 'C';
    //char c_player = 'P';
    //char c_enemy = 'E';
    //char c_item = 'I';

    //TILEMAP    
    TileMap* tile_map = new TileMap(20, 13, 40);
    Entity* player = new Entity(*tile_map, ORANGE, ECollisionType::IGNORE);
    Entity* enemy = new Entity(*tile_map, PURPLE, ECollisionType::BLOCKING);



    if (enemy) 
    {
        enemy->SetLocation(4, 4);
    }

    if (player)
    {
        printf("valid\n");
        player->SetLocation(1, 1);
    }

    if (tile_map)
    {
        tile_map->entities.push_back(*player);
        tile_map->entities.push_back(*enemy);
    }
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        //Draw stuff
        if (tile_map)
        {
            tile_map->Draw();
          //  printf("\nCoord X: %d, Coord Y: %d\n", tile_map->entities[1].GetCoordinates().x, tile_map->entities[1].GetCoordinates().y);
        }

        if (player)
        {
            player->Draw();
            printf("\nCoord X: %d, Coord Y: %d\n", player->GetCoordinates().x, player->GetCoordinates().y);
        }

        if (enemy)
        {
            enemy->Draw();
        }

        if (IsKeyPressed(KEY_D))
        {
            //int x = player->GetCoordinates().tileMapX;
            //x++;
            if (player->bCanMove)
            {
                int y = player->GetCoordinates().y;
                y += 1;
                player->SetLocation(player->GetCoordinates().x, y);
            }

        }
        if (IsKeyPressed(KEY_A))
        {
            if (player->bCanMove)
            {
                int y = player->GetCoordinates().y;
                y-=1;
                player->SetLocation(player->GetCoordinates().x, y);
            }
        }
        if (IsKeyPressed(KEY_W))
        {
           // if(player->bCanMove)
            if (player->bCanMove)
            {
                int x = player->GetCoordinates().x;
                x -= 1;
                player->SetLocation(x, player->GetCoordinates().y);
            }
                   
        }
        if (IsKeyPressed(KEY_S))
        {
            if (player->bCanMove)
            {
                int x = player->GetCoordinates().x;
                x += 1;
                player->SetLocation(x, player->GetCoordinates().y);
            }
        }
   
        //for (size_t i = 0; i < tiles.size(); i++)
        //{
        //    DrawRectangleRec(tiles[i], RED);
        //    if (i % 2 == 0 && i != 0)
        //    {
        //       
        //        DrawRectangleRec(tiles[i], BLUE);
        //    }
        //    if(i ==0)
        //    {
        //        DrawRectangleRec(tiles[i], BLUE);
        //    }
        //    tileNumber = std::to_string(i);
        //    DrawText(tileNumber.c_str(), tiles[i].x, tiles[i].y, 20, WHITE);
        //    
        //}

        //DrawRectangleRec(player, ORANGE);
        // SetPosition(player, tiles, posY, posX);


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