#include "Entity.h"
#include <iostream>

#define PRINT(x) std::cout << "\n";  printf(x) ; std::cout << "\n";

Entity::Entity(TileMap& tile_map_, Color color_, ECollisionType collision_type_)
{
	bActive = true;
	bCanMove = true;
	row = 0;
	column = 0; 
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
	return TileMapCoordinates(row, column);
}

void Entity::SetLocation(int row_, int column_)
{
	if (!tile_map)
	{
		printf("\nInvalid Tile map\n");
		return;
	}

	//int temp_row = row_;
	//int temp_colum = column_;

	//tile_map->tiles[GetTileNumber(row_, column_)].x;
	//tile_map->tiles[GetTileNumber(row_, column_)].y;


	//Do a check if there some entity there
	for (auto& entity : tile_map->entities)
	{
		if (&entity != this && row_ == entity.row && column_ == entity.column && entity.collision_type == ECollisionType::BLOCKING)
		{	
			return;
		}
	}
	entity.x = tile_map->tiles[GetTileNumber(row_, column_)].x;
	entity.y = tile_map->tiles[GetTileNumber(row_, column_)].y;
	row = row_;
	column = column_;



}
