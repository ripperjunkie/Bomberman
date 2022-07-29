#pragma once

#include <raylib.h>
#include <stdio.h>
#include <string>
#include "TileMap.h"


//Simple struct that holds two values for rec crop location when cycling between animation
struct RecCropLocation
{
	float x;
	float y;
};

struct AnimationData
{
	std::vector<RecCropLocation>& rec_crop_location;
};

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

inline TileMapCoordinates operator+(const TileMapCoordinates& one, const TileMapCoordinates& second)
{
	const int x = one.x + second.x;
	const int y = one.y + second.y;
	return TileMapCoordinates(x, y);
}

inline TileMapCoordinates operator-(const TileMapCoordinates& one, const TileMapCoordinates& second)
{
	const int x = one.x - second.x;
	const int y = one.y - second.y;
	return TileMapCoordinates(x, y);
}

inline TileMapCoordinates operator/(const TileMapCoordinates& one, const float second)
{
	const int x = one.x / second;
	const int y = one.y / second;
	return TileMapCoordinates(x, y);
}


//Acting as collision filter
enum class ECollisionType : uint8_t
{
	IGNORE,
	BLOCKING,
	OVERLAP
};

enum class EObjectMovType : uint8_t
{
	STATIC,
	MOVABLE
};

class Entity
{
public:
	Entity(TileMap& tile_map_, ECollisionType collision_type_ = ECollisionType::IGNORE, EObjectMovType object_mov_type_ = EObjectMovType::MOVABLE, bool bShow_collision_ = true, Texture2D shared_sprite_sheet_ = Texture2D());
	~Entity();

	bool GetActiveState() const
	{
		return bActive;
	}
	TileMapCoordinates GetCoordinates();


	void SetLocation(int row_, int column_);
	void SetLocation(int tile_number_);
	void AddMovement(int x, int y);
	void SetActiveState(bool ActiveState)
	{
		bActive = ActiveState;
	}

	virtual void Update();
	virtual void Destroy();
	int row;
	int column;

	void UpdateAnimation();

	//movement
	float speed;
	std::string name;
	void SetShowCollision(bool ShowCollision);
	void ProcessCollision();

	Vector2 movement;
	Rectangle entity_collision;
	EObjectMovType object_mov_type;
	ECollisionType collision_type;
	Vector2 direction_movement; //direction that this object is moving to
	float acceleration = 1.f;


	void MoveOutOfCollision(int x, int y);
protected:
	TileMap* tile_map = nullptr;
	Color color;
	
	//Texture related stuff
	Texture2D entity_texture;
	Texture2D shared_sprite_sheet;
	Rectangle rec_crop_entity_texture;

	//Animation related
	int current_frame;
	int frame_counter;
	float frame_speed = 5.f;
	std::vector<AnimationData> animations;
	int current_animation;

	int GetTileNumber(int row_, int column_)
	{
		if (tile_map)
		{
			return row_ + tile_map->amount_x + column;
		}
		return 0;
	}

	virtual void OnCollisionOverlap(Entity& overlapped_actor_);
	virtual void OnTouchedBlockCollision(Entity& touched_actor_)
	{
		//printf("\ntouched actor\n");
	}

	bool bShow_collision;
	bool bActive;
};

