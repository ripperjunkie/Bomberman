#pragma once

#include "Engine/GameFramework/Actor.h"

class HealthComponent;

class Enemy : public Actor
{
public:
	Enemy() : Actor()
	{
		idle.push_back(RecCropLocation(0, 384));
		mAnimations.push_back(AnimationData(idle));
		CropSprite(idle[0].x, idle[0].y);
	}
    std::vector<RecCropLocation> idle;

	virtual void Start() override;
protected:

    virtual void OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor) override;
	void OnDie();

	// components
	std::shared_ptr<HealthComponent> healthComp;
};

