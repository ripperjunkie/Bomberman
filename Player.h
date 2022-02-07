#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(TileMap& tile_map_, ECollisionType collision_type_ = ECollisionType::IGNORE, bool bShow_collision_ = true) :

        Entity(tile_map_, collision_type_, bShow_collision_)
	{
        entity_texture = LoadTexture("resources/133670.png");
        entity_texture.width = 512.f * 1.F;
        entity_texture.height = 832.f * 1.F;

        rec_crop_entity_texture.x = 32.f * 5.f;
        rec_crop_entity_texture.y = 32.f;
        rec_crop_entity_texture.width = 32.f;
        rec_crop_entity_texture.height = 32.f;
	}


protected:

	virtual void CollisionOverlap(Entity& overlapped_actor_) override;
};

