#pragma once

#include "Engine/GameFramework/Actor.h"

class Explosion : public Actor
{
public:
	Explosion(TileMap& tile_map_, ECollisionType collision_type_ = ECollisionType::OVERLAP, EObjectMovType object_mov_type = EObjectMovType::MOVABLE,
		bool bShow_collision_ = true, Texture2D shared_sprite_sheet_ = Texture2D()) :
		Actor(tile_map_, collision_type_, object_mov_type, bShow_collision_, shared_sprite_sheet_)
	{
		CropSprite(224.f, 704.f);

		name = "explosion";
		Start();
	}

	virtual void Start() override;
	virtual void Update() override;
	virtual void Destroy() override;

	float timer;
	bool bStartTimer;
};
