#pragma once

#include "Engine/GameFramework/Actor.h"

class Explosion;

class Bomb : public Actor
{
public:
	Bomb() : Actor()
	{
		CropSprite(224.f, 704.f);
		mName = "bomb";
		mCollisionType = ECollisionType::OVERLAP;
		mObjectMovementType = EObjectMovType::MOVABLE;
	}

	virtual void Start() override;
	virtual void Update() override;
	virtual void OnCollisionEndOverlap(Actor& other_actor) override;
	virtual void Destroy() override;
	void Explode();



	
	int explosionRange; // controls the range of this bomb when it explodes

private:
	float timer;
	float initialTimer; //using to reset timer back to default value
	bool bStartTimer;
}; 
