#pragma once

#include <raylib.h>
#include <stdio.h>
#include "TileMap.h"

struct TileMapCoordinates
{
public:
	int x;
	int y;
	
	TileMapCoordinates(int tileMapX_, int tileMapY_)
	{
		x = tileMapX_;
		y = tileMapY_;
	}

};

//Acting as collision filter
enum class ECollisionType : uint8_t
{
	IGNORE,
	BLOCKING,
	OVERLAP
};

class Entity
{
public:
	Entity(TileMap& tile_map_, Color color_, ECollisionType collision_type_ = ECollisionType::IGNORE);

	bool GetActiveState() const
	{
		return bActive;
	}
	TileMapCoordinates GetCoordinates();


	void SetLocation(int row_, int column_);
	void SetActiveState(bool ActiveState)
	{
		bActive = ActiveState;
	}

	void Draw();
	virtual void Destroy();
	int row;
	int column;

	bool bCanMove;
protected:
	Rectangle entity;
	TileMap* tile_map = nullptr;
	Color color;
	ECollisionType collision_type;
	
	int GetTileNumber(int row_, int column_)
	{
		if (tile_map)
			return row_ + tile_map->amount_x + column;
		return 0;
	}


private: 
	bool bActive;


};

