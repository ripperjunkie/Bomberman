#pragma once

#include "Engine/GameFramework/Actor.h"

class Enemy : public Actor
{
public:
    Enemy(TileMap& tile_map_, ECollisionType collision_type_ = ECollisionType::IGNORE, EObjectMovType object_mov_type = EObjectMovType::MOVABLE, bool bShow_collision_ = true, Texture2D shared_sprite_sheet_ = Texture2D()) :
        Actor(tile_map_, collision_type_, object_mov_type, bShow_collision_, shared_sprite_sheet_)
    {
        idle.push_back(RecCropLocation(0, 384));

        animations.push_back(AnimationData(idle));

        CropSprite(idle[0].x, idle[0].y);
    }

    std::vector<RecCropLocation> idle;
protected:

    virtual void OnCollisionBeginOverlap(Actor& overlapped_actor_) override;
};
