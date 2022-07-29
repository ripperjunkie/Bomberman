#pragma once

#include "Entity.h"

enum class EBlockType : uint8_t
{
    DESTRUCTIBLE,
    NON_DESTRUCTIBLE
};


class Environment : public Entity
{
public:
    Environment(TileMap& tile_map_, ECollisionType collision_type_ = ECollisionType::IGNORE, EObjectMovType object_mov_type = EObjectMovType::MOVABLE, bool bShow_collision_ = true, Texture2D shared_sprite_sheet_ = Texture2D()) :
        Entity(tile_map_, collision_type_, object_mov_type, bShow_collision_, shared_sprite_sheet_)
	{
        entity_texture = LoadTexture("resources/133670.png");
        entity_texture.width = 512.f * 1.F;
        entity_texture.height = 832.f * 1.F;

        rec_crop_entity_texture.x = 0.f;
        rec_crop_entity_texture.y = 0.f;
        rec_crop_entity_texture.width = 32.f;
        rec_crop_entity_texture.height = 32.f;

	}

    virtual void OnCollisionOverlap(Entity& overlapped_actor_) override;
};

