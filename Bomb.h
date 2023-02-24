#pragma once

#include "Entity.h"

class Bomb : public Entity
{
public:
	Bomb(TileMap& tile_map_, ECollisionType collision_type_ = ECollisionType::OVERLAP, EObjectMovType object_mov_type = EObjectMovType::MOVABLE,
		bool bShow_collision_ = true, Texture2D shared_sprite_sheet_ = Texture2D()) :
		Entity(tile_map_, collision_type_, object_mov_type, bShow_collision_, shared_sprite_sheet_)
	{
		entity_texture = LoadTexture("resources/133670.png");
		entity_texture.width = 512;
		entity_texture.height = 832;

		rec_crop_entity_texture.x = 224.f;
		rec_crop_entity_texture.y = 704.f;
		rec_crop_entity_texture.width = 32.f;
		rec_crop_entity_texture.height = 32.f;
		name = "bomb";
		Start();
	}

	virtual void Update() override;
	virtual void Start() override;
	float timer;
	bool bStartTimer;
}; 