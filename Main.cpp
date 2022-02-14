#define SCREEN_X 1280   
#define SCREEN_Y 720
#define TILE_X 15 
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
#include "Player.h"
#include "Enemy.h"


int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = SCREEN_X;    
    const int screenHeight = SCREEN_Y;


    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

 
    ////Simple and efficient way to setup tile map
    //wchar_t wc_level_ = L'CCC';
    //char c_collider = 'C';
    //char c_player = 'P';
    //char c_enemy = 'E';
    //char c_item = 'I';

    Texture2D sprite_sheet = LoadTexture("resources/133670.png");
    sprite_sheet.width = 512.f * 1.F;
    sprite_sheet.height = 832.f * 1.F;

    //TILEMAP    
    TileMap* tile_map = new TileMap(SCREEN_X / 2.f - ((15.f * 40.f) / 2.f), SCREEN_Y / 2.f - ((13.f * 40.f) / 2.f), 15, 13, 40);
    Player* player = new Player(*tile_map, ECollisionType::BLOCKING,true, sprite_sheet);
    Enemy* enemy = new Enemy(*tile_map, ECollisionType::OVERLAP,true, sprite_sheet);


   if (enemy) 
   {
       enemy->SetLocation(1, 3);
   }

    if (player)
    {
        printf("valid\n");
        player->SetLocation(0, 1);
    }

    if (tile_map)
    {
        tile_map->entities.push_back(*player);
        tile_map->entities.push_back(*enemy);
    }


    Camera2D camera2D = { 0 };
    camera2D.zoom = 1.f;


    int i = 0;
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        camera2D.zoom += ((float)GetMouseWheelMove() * 0.05f);
        
       // printf("\ni = %d\n", i);
        if (enemy)
        {
            //DEBUG OTHER ENTITY MOVEMENT
            if (IsKeyDown(KEY_RIGHT))
            {
                enemy->AddMovement(10,0);
            }
            if (IsKeyDown(KEY_LEFT))
            {
                enemy->AddMovement(-10, 0);
            }
            if (IsKeyDown(KEY_UP))
            {
                enemy->AddMovement(0, -10);
            }
            if (IsKeyDown(KEY_DOWN))
            {
                enemy->AddMovement(0, 10);
            }
        }


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode2D(camera2D);    

        

        //Draw stuff
        if (tile_map)
        {
            tile_map->Draw();
            //printf("\nCoord X: %d, Coord Y: %d\n", tile_map->entities[1].get().GetCoordinates().x, tile_map->entities[1].get().GetCoordinates().y);
        }
        if (enemy)
        {
            enemy->Update();
        }

        if (player)
        {
            player->Update();
           // printf("\nCoord X: %d, Coord Y: %d\n", player->GetCoordinates().x, player->GetCoordinates().y);
        }
       // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndMode2D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}