#include "TileMap.h"
#include "Entity.h"
#include "iostream"
#include "raymath.h"

TileMap::TileMap(unsigned int start_pos_x_, unsigned int start_pos_y_, int amountX_, unsigned int amountY_, unsigned int size_)
{
	amount_x = amountX_;
	amount_y = amountY_;
	size = size_;
	tile_number = '0';

	for (size_t i = 0; i < amount_x * amount_y; i++)
	{
		tiles.push_back(Rectangle());
		tiles[i].width = size;
		tiles[i].height = size;
		tiles[i].x = start_pos_x_;
		tiles[i].y = start_pos_y_;
	}

	float store_y = start_pos_y_;

	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (i != 0)
		{
			tiles[i].x = tiles[i - 1].x + size + 1.f;
			tiles[i].y = store_y;
		}

		if (i % amount_x == 0 && i != 0)
		{
			store_y = tiles[i - 1].y + size + 1.f;
			tiles[i].x = start_pos_x_;
			tiles[i].y = store_y;
		}
	}
}

void TileMap::Draw()
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		//DrawRectangleRec(tiles[i], RED);
		if (i % 2 == 0 && i != 0)
		{
			//DrawRectangleRec(tiles[i], BLUE);
		}
		if (i == 0)
		{
			//DrawRectangleRec(tiles[i], BLUE);
		}
		tile_number = std::to_string(i);
		//DrawText(tile_number.c_str(), tiles[i].x, tiles[i].y, 20, WHITE);
	}

	GetFrameRate();

}

//Solving collision
void TileMap::CollisionCheck()
{
	if (entities.size() == 0)
		return;
	
	//let's find entities that have collision on
	for (uint32_t i(0); i < entities.size(); ++i)
	{
		Entity& entity_1 = entities[i];
		Vector2 entity_1_center = Vector2(entity_1.entity_collision.x + entity_1.entity_collision.width / 2,
			entity_1.entity_collision.y + entity_1.entity_collision.height / 2);
	
		for (uint32_t k(i + 1); k < entities.size(); ++k)
		{
			Entity& entity_2 = entities[k];
			Vector2 entity_2_center = Vector2(entity_2.entity_collision.x + entity_2.entity_collision.width / 2,
				entity_2.entity_collision.y + entity_2.entity_collision.height / 2);
	
			Vector2 dir = Vector2Subtract(entity_1_center, entity_2_center);
			const float dist = Vector2Length(dir);
	
			bool collision_query = entity_1.collision_type != ECollisionType::IGNORE && entity_2.collision_type != ECollisionType::IGNORE && entity_2.collision_type == ECollisionType::BLOCKING;
			if (CheckCollisionRecs(entity_1.entity_collision, entity_2.entity_collision) && collision_query )
			{				
				if (entity_1.object_mov_type == EObjectMovType::MOVABLE)
				{			
					const Vector2 n = Vector2Divide(dir, dist);
					if (dir.x != 0.f && dir.y != 0.f)
					{
						entity_1.MoveOutOfCollision(dir.x * .5f, dir.y * 5.f);
					}
					else
					{
						entity_1.MoveOutOfCollision(1.f * .5f, 1.f * 5.f);
					}
				}
			}
		}
	}
}

void TileMap::GetFrameRate()
{
	std::string frame = std::to_string(GetFPS());
	DrawText(frame.c_str(), 0, 0, 24, YELLOW);
}

void TileMap::Update()
{
	for (auto& element : entities)
	{
		element.get().Update();
		//std::cout << element.get().name << std::endl;
	}
}