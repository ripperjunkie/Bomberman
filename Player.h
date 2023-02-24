#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player(TileMap& tile_map_, ECollisionType collision_type_ = ECollisionType::IGNORE, EObjectMovType object_mov_type = EObjectMovType::MOVABLE,
        bool bShow_collision_ = true, Texture2D shared_sprite_sheet_ = Texture2D()) : 
        Entity(tile_map_, collision_type_, object_mov_type, bShow_collision_, shared_sprite_sheet_)
	{
        idle.push_back(RecCropLocation(0, 32));

        walk_horizontal.push_back(RecCropLocation(97, 32));
        walk_horizontal.push_back(RecCropLocation(128, 32));
        walk_horizontal.push_back(RecCropLocation(160, 32));

        walk_up.push_back(RecCropLocation(0, 65));
        walk_up.push_back(RecCropLocation(32, 65));
        walk_up.push_back(RecCropLocation(64, 65));

        walk_down.push_back(RecCropLocation(34, 32));
        walk_down.push_back(RecCropLocation(64, 32));

        entity_texture = LoadTexture("resources/133670.png");
        entity_texture.width = 512.f * 1.F;
        entity_texture.height = 832.f * 1.F;

        rec_crop_entity_texture.x = idle[0].x;
        rec_crop_entity_texture.y = idle[0].y;
        rec_crop_entity_texture.width = 32.f;
        rec_crop_entity_texture.height = 32.f;

        //Load animations
        animations.push_back(AnimationData(idle));
        animations.push_back(AnimationData(walk_horizontal));
        animations.push_back(AnimationData(walk_up));
        animations.push_back(AnimationData(walk_down));
        
    }
    virtual void Update() override;
    void Input();
    void InputMovement();
    void InputSpawnBomb();
    


    std::vector<RecCropLocation> idle;
    std::vector<RecCropLocation> walk_horizontal;
    std::vector<RecCropLocation> walk_up;
    std::vector<RecCropLocation> walk_down;

    float input_up;
    float input_right;

protected:

	virtual void OnCollisionOverlap(Entity& overlapped_actor_) override;
};

