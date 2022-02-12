#pragma once
#include "Entity.h"


class Player : public Entity
{
public:
	Player(TileMap& tile_map_, ECollisionType collision_type_ = ECollisionType::IGNORE, bool bShow_collision_ = true, Texture2D shared_sprite_sheet_ = Texture2D()) : 
        Entity(tile_map_, collision_type_, bShow_collision_, shared_sprite_sheet_)
	{
        entity_texture = LoadTexture("resources/133670.png");
        entity_texture.width = 512.f * 1.F;
        entity_texture.height = 832.f * 1.F;

        rec_crop_entity_texture.x = 0.f;
        rec_crop_entity_texture.y = 0.f;
        rec_crop_entity_texture.width = 32.f;
        rec_crop_entity_texture.height = 32.f;

        //Load animations
        animations.push_back(AnimationData(33, 96, 224,32, 0)); //walk right
        animations.push_back(AnimationData(33, 0, 96, 32,0)); //walk down
        animations.push_back(AnimationData(33, 0, 96, 64, 0)); //walk up


        
    }
    virtual void Update() override;


    void Movement();
protected:

	virtual void CollisionOverlap(Entity& overlapped_actor_) override;
};

