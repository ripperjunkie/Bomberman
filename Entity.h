#pragma once

#include <raylib.h>
#include <stdio.h>
#include "TileMap.h"

struct AnimationData
{
	int animation_length;
	int animation_start_pos_x;
	int animation_final_pos_x;
	int animation_start_pos_y;
	int animation_final_pos_y;

	AnimationData() : animation_length(0), animation_start_pos_x(0), animation_final_pos_x(0), animation_start_pos_y(0), animation_final_pos_y()
	{

	}

	AnimationData(int animation_length_, int animation_start_pos_x_, int animation_final_pos_x_, int animation_start_pos_y_, int animation_final_pos_y_)
	{
		animation_length = animation_length_;
		animation_start_pos_x = animation_start_pos_x_;
		animation_final_pos_x = animation_final_pos_x_;
		animation_start_pos_y = animation_start_pos_y_;
		animation_final_pos_y = animation_final_pos_y;
	}
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
	Entity(TileMap& tile_map_, ECollisionType collision_type_ = ECollisionType::IGNORE,	bool bShow_collision_ = true, Texture2D shared_sprite_sheet_ = Texture2D() );
	~Entity();

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

	virtual void Update();
	virtual void Destroy();
	int row;
	int column;

	void UpdateAnimation();
protected:
	Rectangle entity_collision;
	TileMap* tile_map = nullptr;
	Color color;
	ECollisionType collision_type;
	
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
			return row_ + tile_map->amount_x + column;
		return 0;
	}
	virtual void CollisionOverlap(Entity& overlapped_actor_);


	bool bShow_collision;
	bool bActive;

};

