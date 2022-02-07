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


//@PARAMS: class, tileMap coordinates
Entity* Spawn()
{
    //TODO
    return NULL;
}

//Move entity with input
void Movement(Entity* entity)
{
    if (!entity) return;
    
    if (IsKeyPressed(KEY_D))
    {
        int x = entity->GetCoordinates().x;
        x += 1;
        printf("can move %d", x);
        entity->SetLocation(entity->GetCoordinates().y, x);
    }
    if (IsKeyPressed(KEY_A))
    {
        int x = entity->GetCoordinates().x;
        x -= 1;
        entity->SetLocation(entity->GetCoordinates().y, x);
    }
    if (IsKeyPressed(KEY_W))
    {
        int y = entity->GetCoordinates().y;
        y -= 1;
        entity->SetLocation(y, entity->GetCoordinates().x);
    }
    if (IsKeyPressed(KEY_S))
    {
        int y = entity->GetCoordinates().y;
        y += 1;
        entity->SetLocation(y, entity->GetCoordinates().x);

    }
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 900;    
    const int screenHeight = 850;


    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

 
    ////Simple and efficient way to setup tile map
    //wchar_t wc_level_ = L'CCC';
    //char c_collider = 'C';
    //char c_player = 'P';
    //char c_enemy = 'E';
    //char c_item = 'I';

    //TILEMAP    
    TileMap* tile_map = new TileMap(15, 13, 40);
    Player* player = new Player(*tile_map, ECollisionType::OVERLAP);
    Entity* enemy = new Entity(*tile_map, ECollisionType::OVERLAP);

    //Texture2D test;
    //test = LoadTexture("resources/133670.png");
    //test.width = 521.f * 1.f;
    //test.height = 832.f * 1.f;
    //Rectangle tile;
    //tile.x = 32.f;
    //tile.y = 0.f;
    //tile.width = 521.f;
    //tile.height = 832.f;
    //Rectangle tile_destination;
    //tile.x = 0.f;
    //tile.y = 32.f;
    //tile.width = 32.f;
    //tile.height = 32.f;
    //Vector2 text_pos;
    //text_pos.x = 0.f;
    //text_pos.y = 0.f;


   if (enemy) 
   {
       enemy->SetLocation(4, 4);
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
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        camera2D.zoom += ((float)GetMouseWheelMove() * 0.05f);
        
        //Player movement
        Movement(player);

        if (enemy)
        {
            //DEBUG OTHER ENTITY MOVEMENT
            if (IsKeyPressed(KEY_RIGHT))
            {

                int x = enemy->GetCoordinates().x;
                x += 1;
                printf("can move %d", x);
                enemy->SetLocation(enemy->GetCoordinates().y, x);
            }
            if (IsKeyPressed(KEY_LEFT))
            {
                int x = enemy->GetCoordinates().x;
                x -= 1;
                enemy->SetLocation(enemy->GetCoordinates().y, x);
            }
            if (IsKeyPressed(KEY_UP))
            {
                int y = enemy->GetCoordinates().y;
                y -= 1;
                enemy->SetLocation(y, enemy->GetCoordinates().x);

            }
            if (IsKeyPressed(KEY_DOWN))
            {
                int y = enemy->GetCoordinates().y;
                y += 1;
                enemy->SetLocation(y, enemy->GetCoordinates().x);
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

        if (player)
        {
            player->Draw();

            player->DrawActor();
           // printf("\nCoord X: %d, Coord Y: %d\n", player->GetCoordinates().x, player->GetCoordinates().y);
        }

       if (enemy)
       {
           enemy->Draw();  
          // printf("\n valid! address %p\n", &enemy);
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