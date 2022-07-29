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
#include "Environment.h"


int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = SCREEN_X;
	const int screenHeight = SCREEN_Y;


	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
	SetTargetFPS(120); // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	Texture2D sprite_sheet = LoadTexture("resources/133670.png");
	sprite_sheet.width = 512.f * 1.F;
	sprite_sheet.height = 832.f * 1.F;

	//TILEMAP    
	TileMap* tile_map = new TileMap(SCREEN_X / 2.f - ((15.f * 40.f) / 2.f), SCREEN_Y / 2.f - ((13.f * 40.f) / 2.f), 15, 13, 40);
	Player* player = new Player(*tile_map, ECollisionType::BLOCKING, EObjectMovType::MOVABLE, true, sprite_sheet);
	Enemy* enemy_02 = new Enemy(*tile_map, ECollisionType::BLOCKING, EObjectMovType::STATIC, true, sprite_sheet);
	Enemy* enemy_03 = new Enemy(*tile_map, ECollisionType::BLOCKING, EObjectMovType::STATIC, true, sprite_sheet);
	Enemy* enemy_04 = new Enemy(*tile_map, ECollisionType::BLOCKING, EObjectMovType::STATIC, true, sprite_sheet);
	Enemy* enemy_05 = new Enemy(*tile_map, ECollisionType::BLOCKING, EObjectMovType::STATIC, true, sprite_sheet);

	if (player)
	{
		player->SetLocation(0);
		player->name = "Player";
		player->SetShowCollision(true);
	}

	std::vector<std::reference_wrapper<Entity>> enemies;
	for (uint8_t i(0); i < 10; ++i)
	{
		enemies.push_back(*new Enemy(*tile_map, ECollisionType::BLOCKING, EObjectMovType::STATIC, true, sprite_sheet));
	}
	for (uint8_t i(0); i < 10; ++i)
	{
		enemies[i].get().SetLocation(i + 1);
	}

	if (tile_map)
	{
		tile_map->entities.push_back(*player);
		for (auto& element : enemies)
		{
			tile_map->entities.push_back(element);
		}
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
		if (IsKeyDown(KEY_RIGHT))
		{
			camera2D.offset.x -= .5f;
		}
		if (IsKeyDown(KEY_LEFT)) {
			camera2D.offset.x += .5f;
		}
		if (IsKeyDown(KEY_UP)) {
			camera2D.offset.y += .5f;
		}
		if (IsKeyDown(KEY_DOWN)) {
			camera2D.offset.y -= .5f;
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
			tile_map->CollisionCheck();
		}

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