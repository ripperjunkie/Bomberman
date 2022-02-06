#include "Entity.h"
#include <iostream>

#define PRINT(x) std::cout << "\n";  printf(x) ; std::cout << "\n";

Entity::Entity(TileMap& tile_map_, Color color_, ECollisionType collision_type_)
{
	bActive = true;
	bCanMove = true;
	row = 1;
	column = 1; 
	tile_map = &tile_map_;
	collision_type = collision_type_;


	if (tile_map)
	{
		entity.width = (float)tile_map->size;
		entity.height = (float)tile_map->size;
	}

	entity.x = 0;
	entity.y = 0;
	color = color_;
}

void Entity::Draw()
{
	DrawRectangleRec(entity, color);
}

void Entity::Destroy()
{

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
			printf("\nOVERLAPPED\n");
		}
	}
	column = column_;
	row = row_; ;
 
	entity.x = tile_map->tiles[column].x;
	entity.y = tile_map->tiles[(tile_map->amount_x * row) + column].y;
	

}
