#include "Game.h"

#include "Engine/Public/Utils.h"
#include "Engine/Grid.h"
#include "Engine/GameFramework/Actor.h"
#include "Engine/Managers/ActorManager.h"

#include "Game/Player.h"
#include "Game/Enemy.h"
#include "Game/Environment.h"
#include "Game/Brick.h"
#include "Game/GameUtils.h"



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
					levelJson.push_back(data[j].GetInt());
				}
			}
		}
	}

	//Get the tile width, height
	TileSetting tileSetting = { document["width"].GetInt(), document["height"].GetInt() };
#pragma endregion

	// Initialize raylib window
	InitWindow(SCREEN_X, SCREEN_Y, "raylib [core] example - basic window");
	SetTargetFPS(120);



	// Initialize camera
	Camera2D camera = { 0 };
	camera.zoom = 1.0f;
	camera.offset = Vector2{ 0,0 };

#pragma region Load Sprite sheet
	Texture2D mSpriteSheet = LoadTexture("resources/133670.png");
	mSpriteSheet.width = 512.f;
	mSpriteSheet.height = 832.f;
#pragma endregion




#pragma region Spawning and placing Stuff On Level
	{
		std::shared_ptr<Grid> grid = std::make_shared<Grid>
			(
				SCREEN_X / 2.f - ((15.f * 40.f) / 2.f), SCREEN_Y / 2.f - ((13.f * 40.f) / 2.f),
				tileSetting.width, tileSetting.height, TILE_SIZE
			);

		for (int i = 0; i < levelJson.size(); ++i)
		{
			if (levelJson[i] == ENVIRONMENT)
			{
				ActorManager::GetInstance()->SpawnActor<Environment>()->SetLocation(grid->tiles[i].x, grid->tiles[i].y);
			}
			if (levelJson[i] == PLAYER)
			{
				// spawn player
				ActorManager::GetInstance()->SpawnActor<Player>()->SetLocation(grid->tiles[i].x, grid->tiles[i].y);
			}

			if (levelJson[i] == BRICK)
			{
				ActorManager::GetInstance()->SpawnActor<Brick>()->SetLocation(grid->tiles[i].x, grid->tiles[i].y);
			}
			if (levelJson[i] == ENEMY_A)
			{
				ActorManager::GetInstance()->SpawnActor<Enemy>()->SetLocation(grid->tiles[i].x, grid->tiles[i].y);
			}
		}
	}

#pragma endregion

	// TO BE REMOVED!!!
	// registering entities
	for (int i = 0; i < ACTOR_MANAGER->GetActors().size(); ++i)
	{
		// make sure we don't register the same overlapped entity in itself
		if (ACTOR_MANAGER->GetActors()[i] != ACTOR_MANAGER->GetActors()[i])
		{
			ACTOR_MANAGER->GetActors()[i]->overlapped_entities.emplace
			(
				ACTOR_MANAGER->GetInstance()->GetActors()[i], false
			);
		}
	}



	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Start drawing...
		BeginDrawing();
		{
			ClearBackground(BLACK);

			BeginMode2D(camera);

			//Update world
			ACTOR_MANAGER->Update();

			// just to clear console
			if (IsKeyPressed(KEY_F))
			{
				CLEAR_CLS;
			}

			// display fps (debug)
			{
				std::string frame = "FPS: ";
				frame += std::to_string(GetFPS());
				DrawText(frame.c_str(), 0, 0, 24, YELLOW);
			}
			EndMode2D();
		}	

		EndDrawing();
	}

	CloseWindow();        // Close window and OpenGL context
}