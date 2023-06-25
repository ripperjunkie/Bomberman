
#include "Engine/Public/Utils.h"
#include "Engine/TileMap.h"
#include "Engine/GameFramework/Actor.h"
#include "Game/Player.h"
#include "Game/Enemy.h"
#include "Game/Environment.h"

#include "lib/rapidjson-master/include/rapidjson/document.h"
#include <fstream>



struct TileSetting
{
	int width;
	int height;
};

int main()
{
	std::vector<int> levelJson;
#pragma region JSON
	// Open the JSON file for reading
	std::ifstream file("resources/Tiles/level-01-test.json");
	if (!file.is_open())
	{
		std::cerr << "Failed to open file!" << std::endl;
		return 1;
	}

	// Read the entire file contents into a string
	std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	// Parse the JSON data
	rapidjson::Document document;
	document.Parse(contents.c_str()); //this method prob is very miraculous, parsing things can be hard

	// Access the values in the JSON document
	if (document.HasMember("layers") && document["layers"].IsArray())
	{
		const rapidjson::Value& layers = document["layers"]; //retrieves value associated with this array
		for (rapidjson::SizeType i = 0; i < layers.Size(); i++)
		{
			if (layers[i].HasMember("data") && layers[i]["data"].IsArray())
			{
				const rapidjson::Value& data = layers[i]["data"]; //retrieves value associated with this array
				for (rapidjson::SizeType j = 0; j < data.Size(); j++)
				{
					//std::cout << data[j].GetInt() << " ";
					levelJson.push_back(data[j].GetInt());
				}
				//std::cout << std::endl;

			}
		}
	}

	//Get the tile width, height
	TileSetting tileSetting = { document["width"].GetInt(), document["height"].GetInt() };
#pragma endregion

	// Initialization
	InitWindow(SCREEN_X, SCREEN_Y, "raylib [core] example - basic window");

	Texture2D sprite_sheet = LoadTexture("resources/133670.png"); //load our sprite sheet
	sprite_sheet.width = 512.f * 1.F;
	sprite_sheet.height = 832.f * 1.F;


	std::shared_ptr<TileMap> level = std::make_shared<TileMap>(SCREEN_X / 2.f - ((15.f * 40.f) / 2.f), SCREEN_Y / 2.f - ((13.f * 40.f) / 2.f), tileSetting.width, tileSetting.height, TILE_SIZE);
	Player* player = new Player(*level, ECollisionType::BLOCKING, EObjectMovType::MOVABLE, true, sprite_sheet);

	if (player)
	{
		player->name = "Player";
		player->SetShowCollision(true);
	}

	std::vector<std::reference_wrapper<Actor>> enemies; //store all entities in an vector with a reference for the entities
	for (int i = 0; i < levelJson.size(); ++i)
	{
		if (levelJson[i] == ENEMY_A)
		{
			enemies.push_back(*new Enemy(*level, ECollisionType::OVERLAP, EObjectMovType::MOVABLE, true, sprite_sheet));

		}
	}
	for (int i = 0; i < enemies.size(); ++i)
	{
		if (&enemies[i])
		{
			enemies[i].get().name = "enemy " + std::to_string(i); //setting name for enemies 
		}
	}


	std::vector<Actor*> blocks;//store all entities in an vector with a reference for the entities
	for (int i = 0; i < levelJson.size(); ++i)
	{
		if (levelJson[i] == BRICK)
		{
			blocks.push_back(&*new Environment(*level, ECollisionType::BLOCKING, EObjectMovType::STATIC, true, sprite_sheet));
		}
	}
	for (int i = 0; i < blocks.size(); ++i)
	{
		if (&blocks[i])
		{
			blocks[i]->name = "blocks " + std::to_string(i); //setting name for blocks
		}
	}


	int counter_blocks = 0;
	int counter_enemy = 0;
	for (int i = 0; i < levelJson.size(); ++i)
	{
		if (levelJson[i] == PLAYER)
		{
			player->SetLocation(i);
		}
		if (levelJson[i] == BRICK)
		{
			if (counter_blocks < blocks.size())
			{
				blocks[counter_blocks]->SetLocation(i);
				counter_blocks++;
			}
		}
		if (levelJson[i] == ENEMY_A)
		{
			if (counter_enemy < enemies.size())
			{
				enemies[counter_enemy].get().SetLocation(i);
				counter_enemy++;
			}
		}
	}

	// registering entities
	for (int i = 0; i < level->entities.size(); ++i)
	{
		if (level->entities[i] == player)
		{
			continue;
		}
		//player->overlapped_entities.emplace(level->entities[i], false);

		// make sure we don't register the same overlapped entity in itself
		if (level->entities[i] != level->entities[i])
		{
			level->entities[i]->overlapped_entities.emplace(level->entities[i], false);	
		}
	}


	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Draw	
		BeginDrawing();


		//Update world
		if (level)
		{
			level->Update();
		}

		// just to clear console
		if (IsKeyPressed(KEY_F))
		{
			system("cls");
		}

		ClearBackground(BLACK);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}