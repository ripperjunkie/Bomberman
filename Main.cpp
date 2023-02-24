#define SCREEN_X 1280   
#define SCREEN_Y 720
#define TILE_X 15 
#define TILE_Y 13 
#define TILE_SIZE 32

#include <raylib.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <map>
#include "iostream"

#include "TileMap.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Environment.h"

//This method helps us to fetch where we want to place entities based on a string tileset
int CharactersNum(std::string& _string, char _context)
{
	int charNum = 0;
	for (uint8_t i(0); i < _string.length(); ++i)
	{
		if (_string[i] == _context)
			charNum++;		
	}
	return charNum;
}


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
	TileMap* tile_map = new TileMap(SCREEN_X / 2.f - ((15.f * 40.f) / 2.f), SCREEN_Y / 2.f - ((13.f * 40.f) / 2.f), TILE_X, TILE_Y, TILE_SIZE);
	Player* player = new Player(*tile_map, ECollisionType::BLOCKING, EObjectMovType::MOVABLE, true, sprite_sheet);

	if (player)
	{
		player->name = "Player";
		player->SetShowCollision(true);
	}

	std::string map_text_format =
		"x x x x x x x x x x x x x x x\n"
		"x 0 0 0 e 0 0 0 e 0 0 0 0 0 x\n"
		"x 0 0 0 0 0 0 0 0 0 0 0 0 0 x\n"
		"x 0 0 0 0 0 0 0 0 0 0 0 0 0 x\n"
		"x 0 0 0 0 0 0 0 0 0 0 0 0 0 x\n"
		"x x x 0 0 0 0 0 0 0 0 0 0 0 x\n"
		"x 0 x 0 0 0 0 0 0 0 0 0 0 0 x\n"
		"x x x 0 0 0 0 0 0 e 0 0 0 0 x\n"
		"x 0 0 0 0 0 0 0 0 0 0 0 0 0 x\n"
		"x 0 0 0 0 0 0 0 0 0 0 x 0 0 x\n"
		"x 0 0 0 0 0 0 0 0 0 x x x 0 x\n"
		"x 0 0 0 0 0 0 0 0 0 0 x 0 p x\n"
		"x x x x x x x x x x x x x x x\n";


	map_text_format.erase(remove(map_text_format.begin(), map_text_format.end(), ' '), map_text_format.end());
	map_text_format.erase(remove(map_text_format.begin(), map_text_format.end(), '\n'), map_text_format.end());	

	std::vector<std::reference_wrapper<Entity>> enemies;
	for (uint8_t i(0); i < CharactersNum(map_text_format, 'e'); ++i)
	{
		enemies.push_back(*new Enemy(*tile_map, ECollisionType::BLOCKING, EObjectMovType::MOVABLE, true, sprite_sheet));
		if (&enemies[i]) {
			enemies[i].get().name = "enemy " + std::to_string(i);
		}
	}

	std::vector<std::reference_wrapper<Entity>> blocks;
	for (uint8_t i(0); i < CharactersNum(map_text_format, 'x'); ++i)
	{
		blocks.push_back(*new Environment(*tile_map, ECollisionType::BLOCKING, EObjectMovType::STATIC, true, sprite_sheet));
		if (&blocks[i]) {
			blocks[i].get().name = "blocks " + std::to_string(i);
		}
	}
	
	int counter_blocks = 0;
	int counter_enemy = 0;
	for (uint8_t i(0); i < map_text_format.length(); ++i)
	{
		if (map_text_format[i] == 'p') {
			player->SetLocation(i);
		}
		if (map_text_format[i] == 'x')
		{
			if (counter_blocks < blocks.size())
			{
				blocks[counter_blocks].get().SetLocation(i);
				counter_blocks++;
			}
		}
		if (map_text_format[i] == 'e')
		{
			if (counter_enemy < enemies.size())
			{
				enemies[counter_enemy].get().SetLocation(i);
				counter_enemy++;
			}
		}
	}

	Camera2D camera2D = { 0 };
	camera2D.zoom = 1.f;
	
	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
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

		if (tile_map)
		{
			tile_map->Draw();
			tile_map->CollisionCheck();
			tile_map->Update();
		}


		EndMode2D();

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------


	//for now I'm gonna delete things manually, but a better solution would be having a wrapper to delete all entities of the game
	delete player;
	delete tile_map;
	for (size_t i = 0; i < enemies.size(); i++)
	{
		delete &enemies[i].get();
	}

	return 0;
}