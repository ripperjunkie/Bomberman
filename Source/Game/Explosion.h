#pragma once

#include "Engine/GameFramework/Actor.h"

class Explosion : public Actor
{
public:
	Explosion();
	virtual void Start() override;
	virtual void Update() override;
	virtual void Destroy() override;
	virtual void OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor) override;


private:
	float timer;
	float initialTimer; //using to reset timer back to default value

	std::vector<RecCropLocation> explosionAnim;
};

