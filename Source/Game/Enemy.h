#pragma once

#include "Engine/GameFramework/Actor.h"

class Enemy : public Actor
{
public:
    Enemy() : Actor()
    {
        
        idle.push_back(RecCropLocation(0, 384));
        animations.push_back(AnimationData(idle));
        CropSprite(idle[0].x, idle[0].y);
    }

    std::vector<RecCropLocation> idle;
	std::shared_ptr<class Grid> tileMap = nullptr;

protected:

    virtual void OnCollisionBeginOverlap(Actor& overlapped_actor_) override;
};

