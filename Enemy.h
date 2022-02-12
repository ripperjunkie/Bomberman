#pragma once

#include "Entity.h"

class Enemy : public Entity
{
public:
    Enemy(TileMap& tile_map_, ECollisionType collision_type_ = ECollisionType::IGNORE, bool bShow_collision_ = true, Texture2D shared_sprite_sheet_ = Texture2D()) :
        Entity(tile_map_, collision_type_, bShow_collision_, shared_sprite_sheet_)
    {
        entity_texture = LoadTexture("resources/133670_copy.png");
        entity_texture.width = 34.f * 1.F;
        entity_texture.height = 33.f * 1.F;

        rec_crop_entity_texture.x = 0.f;
        rec_crop_entity_texture.y = 0.f;
        rec_crop_entity_texture.width = 34.f;
        rec_crop_entity_texture.height = 33.f;
    }


protected:

    virtual void CollisionOverlap(Entity& overlapped_actor_) override;
};

