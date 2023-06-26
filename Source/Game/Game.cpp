#include "Game.h"

#include "Engine/Public/Utils.h"
#include "Engine/TileMap.h"
#include "Engine/GameFramework/Actor.h"
#include "Game/Player.h"
#include "Game/Enemy.h"
#include "Game/Environment.h"

#include "Engine/Managers/ActorManager.h"


#include "lib/rapidjson-master/include/rapidjson/document.h"
#include <fstream>

void Game::Start()
{


#pragma region JSON
	std::vector<int> levelJson;

	// Open the JSON file for reading
	std::ifstream file("resources/Tiles/level-01-test.json");
	if (!file.is_open())
	{
		std::cerr << "Failed to open file!" << std::endl;
		return;
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

	std::shared_ptr<Grid> level = std::make_shared<Grid>
		(
		SCREEN_X / 2.f - ((15.f * 40.f) / 2.f), SCREEN_Y / 2.f - ((13.f * 40.f) / 2.f), 
		tileSetting.width, tileSetting.height, TILE_SIZE
		);


	// Initialization
	InitWindow(SCREEN_X, SCREEN_Y, "raylib [core] example - basic window");

	Texture2D sprite_sheet = LoadTexture("resources/133670.png"); //load our sprite sheet
	sprite_sheet.width = 512.f;
	sprite_sheet.height = 832.f;


	//Player* player = new Player();
	std::shared_ptr<Player> player = ActorManager::GetInstance()->SpawnActor<Player>();

#pragma region Enemies
	std::vector<std::shared_ptr<Enemy>> enemies; //store all entities in a vector with a reference for the entities
	for (int i = 0; i < levelJson.size(); ++i)
	{
		if (levelJson[i] == ENEMY_A)
		{
			enemies.push_back(ActorManager::GetInstance()->SpawnActor<Enemy>());
		}
	}

	// give enemies a name
	for (int i = 0; i < enemies.size(); ++i)
	{
		if (&enemies[i])
		{
			enemies[i]->name = "enemy " + std::to_string(i); //setting name for enemies 
		}
	}
#pragma endregion

#pragma region Bricks
	std::vector<std::shared_ptr<Environment>> bricks;//store all entities in an vector with a reference for the entities
	for (int i = 0; i < levelJson.size(); ++i)
	{
		if (levelJson[i] == BRICK)
		{
			bricks.push_back(ActorManager::GetInstance()->SpawnActor<Environment>());
		}
	}
	for (int i = 0; i < bricks.size(); ++i)
	{
		if (&bricks[i])
		{
			bricks[i]->name = "bricks " + std::to_string(i); //setting name for blocks
		}
	}
#pragma endregion


#pragma region Placing Stuff On Level
	{
		int counter_blocks = 0;
		int counter_enemy = 0;
		for (int i = 0; i < levelJson.size(); ++i)
		{
			if (levelJson[i] == PLAYER)
			{
				player->SetLocation(level->tiles[i].x, level->tiles[i].y);
			}
			if (levelJson[i] == BRICK)
			{
				if (counter_blocks < bricks.size())
				{
					bricks[counter_blocks]->SetLocation(level->tiles[i].x, level->tiles[i].y);
					counter_blocks++;
				}
			}
			if (levelJson[i] == ENEMY_A)
			{
				if (counter_enemy < enemies.size())
				{
					enemies[counter_enemy]->SetLocation(level->tiles[i].x, level->tiles[i].y);
					counter_enemy++;
				}
			}
		}
	}
#pragma endregion

	// registering entities
	for (int i = 0; i < ACTOR_MANAGER->GetActors().size(); ++i)
	{
		// make sure we don't register the same overlapped entity in itself
		if (ACTOR_MANAGER->GetActors()[i] != ACTOR_MANAGER->GetActors()[i])
		{
			ACTOR_MANAGER->GetActors()[i]->overlapped_entities.emplace(ACTOR_MANAGER->GetActors()[i], false);
		}
	}


	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Draw	
		BeginDrawing();


		//Update world
		ACTOR_MANAGER->Update();


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
}