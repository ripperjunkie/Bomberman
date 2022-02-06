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
        if (entity->bCanMove)
        {
            int x = entity->GetCoordinates().x;
            x += 1;
            printf("can move %d", x);
            entity->SetLocation(entity->GetCoordinates().y, x);
        }
    }
    if (IsKeyPressed(KEY_A))
    {
        if (entity->bCanMove)
        {
            int x = entity->GetCoordinates().x;
            x -= 1;
            entity->SetLocation(entity->GetCoordinates().y, x);
        }
    }
    if (IsKeyPressed(KEY_W))
    {
        if (entity->bCanMove)
        {
            int y = entity->GetCoordinates().y;
            y -= 1;
            entity->SetLocation(y, entity->GetCoordinates().x);
        }

    }
    if (IsKeyPressed(KEY_S))
    {
        if (entity->bCanMove)
        {
            int y = entity->GetCoordinates().y;
            y += 1;
            entity->SetLocation(y, entity->GetCoordinates().x);
        }

    }
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
    TileMap* tile_map = new TileMap(15, 13, 40);
    Entity* player = new Entity(*tile_map, ORANGE, ECollisionType::OVERLAP);
    Entity* enemy = new Entity(*tile_map, PURPLE, ECollisionType::BLOCKING);



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


        //DEBUG OTHER ENTITY MOVEMENT
        if (IsKeyPressed(KEY_RIGHT))
        {
            if (enemy->bCanMove)
            {
                int x = enemy->GetCoordinates().x;
                x += 1;
                printf("can move %d", x);
                enemy->SetLocation(enemy->GetCoordinates().y, x);
            }
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            if (player->bCanMove)
            {
                int x = enemy->GetCoordinates().x;
                x -= 1;
                enemy->SetLocation(enemy->GetCoordinates().y, x);
            }
        }
        if (IsKeyPressed(KEY_UP))
        {
            if (enemy->bCanMove)
            {
                int y = enemy->GetCoordinates().y;
                y -= 1;
                enemy->SetLocation(y, enemy->GetCoordinates().x);
            }

        }
        if (IsKeyPressed(KEY_DOWN))
        {
            if (enemy->bCanMove)
            {
                int y = enemy->GetCoordinates().y;
                y += 1;
                enemy->SetLocation(y, enemy->GetCoordinates().x);
            }

        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

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
           // printf("\nCoord X: %d, Coord Y: %d\n", player->GetCoordinates().x, player->GetCoordinates().y);
        }

       if (enemy)
       {
           enemy->Draw();
         //   printf("\nCoord X: %d, Coord Y: %d\n", enemy->GetCoordinates().x, enemy->GetCoordinates().y);
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