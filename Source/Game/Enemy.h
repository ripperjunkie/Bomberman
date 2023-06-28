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

protected:


    virtual void OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor) override;
};

