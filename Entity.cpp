#include "Entity.h"
#include <iostream>

#define PRINT(x) std::cout << "\n";  printf(x) ; std::cout << "\n";

Entity::Entity(TileMap& tile_map_, ECollisionType collision_type_, bool bShow_collision_)
{
	bActive = true;
	row = 1;
	column = 1; 
	tile_map = &tile_map_;
	collision_type = collision_type_;
	bShow_collision = bShow_collision_;
	

	if (tile_map)
	{
		entity_collision.width = (float)tile_map->size;
		entity_collision.height = (float)tile_map->size;
	}

	entity_collision.x = 0.f;
	entity_collision.y = 0.f;
	color = GREEN;
}

Entity::~Entity()
{
	printf("\n I'm going to space!\n");
}

void Entity::Draw()
{
	if(bShow_collision)
		DrawRectangleLinesEx(entity_collision, 2.f, color);
}

void Entity::Destroy()
{
	delete (this);
}

void Entity::CollisionOverlap(Entity& overlapped_actor_)
{
	printf("\n Overlapped\n");
}

void Entity::DrawActor()
{
	Vector2 text_pos;
	text_pos.x = entity_collision.x + 3.f;
	text_pos.y = entity_collision.y + 3.f;
	DrawTextureRec(entity_texture, rec_crop_entity_texture, text_pos, WHITE);
}

TileMapCoordinates Entity::GetCoordinates()
{
	return TileMapCoordinates(column, row);
}

void Entity::SetLocation(int row_, int column_)
{
	if (!tile_map)
	{
		printf("\nInvalid Tile map\n");
		return;
	}

	//Do a check if there some entity there
	for (auto& entity : tile_map->entities)
	{
		if (&entity.get() != this && row_ == entity.get().row && column_ == entity.get().column && entity.get().collision_type == ECollisionType::BLOCKING)
		{	
			printf("cant move");
			return;
		}
		if (&entity.get() != this && row_ == entity.get().row && column_ == entity.get().column && entity.get().collision_type == ECollisionType::OVERLAP)
		{
			CollisionOverlap(entity);
			break;
		}
	}
	column = column_;
	row = row_; ;
 
	entity_collision.x = tile_map->tiles[column].x;
	entity_collision.y = tile_map->tiles[(tile_map->amount_x * row) + column].y;
	

}
