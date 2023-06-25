#pragma once

#include "Engine/GameFramework/Actor.h"



class Bomb;

class Player : public Actor
{
public:
	Player(TileMap& tile_map_, ECollisionType collision_type_ = ECollisionType::IGNORE, EObjectMovType object_mov_type = EObjectMovType::MOVABLE,
        bool bShow_collision_ = true, Texture2D shared_sprite_sheet_ = Texture2D()) : 
        Actor(tile_map_, collision_type_, object_mov_type, bShow_collision_, shared_sprite_sheet_)
	{
        //Here we insert inside the animations array each sprite we want it to be cycling
        idle.push_back(RecCropLocation(0, 32));

        walk_horizontal.push_back(RecCropLocation(97, 32));
        walk_horizontal.push_back(RecCropLocation(128, 32));
        walk_horizontal.push_back(RecCropLocation(160, 32));

        walk_up.push_back(RecCropLocation(0, 65));
        walk_up.push_back(RecCropLocation(32, 65));
        walk_up.push_back(RecCropLocation(64, 65));

        walk_down.push_back(RecCropLocation(34, 32));
        walk_down.push_back(RecCropLocation(64, 32));

        CropSprite(idle[0].x, idle[0].y);

        //Load animations
        animations.push_back(AnimationData(idle));
        animations.push_back(AnimationData(walk_horizontal));
        animations.push_back(AnimationData(walk_up));
        animations.push_back(AnimationData(walk_down));
        
        bCanPlaceBomb = true;
        bStartTimer = false;
        timer = 4.f; //cooldown of player to place bombs
        initialTimer = timer;
        speed = 25.f;
    }

    ~Player();

    virtual void Start() override;
    virtual void Update() override;
    void Input();
    void InputMovement();
    void InputSpawnBomb();
    
    
    //to control animations switching
    std::vector<RecCropLocation> idle;
    std::vector<RecCropLocation> walk_horizontal;
    std::vector<RecCropLocation> walk_up;
    std::vector<RecCropLocation> walk_down;

    float input_up;
    float input_right;
    Bomb* bomb = nullptr;
protected:
	virtual void OnCollisionBeginOverlap(Actor& overlapped_actor_) override;
    virtual void OnCollisionEndOverlap(Actor& other_actor) override;
    
    bool bCanPlaceBomb;
};
