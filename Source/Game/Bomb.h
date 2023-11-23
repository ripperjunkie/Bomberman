#pragma once

#include "Engine/GameFramework/Actor.h"

class Explosion;

class Bomb : public Actor
{
public:
	Bomb();

	virtual void Start() override;
	virtual void Update() override;
	virtual void OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor);
	virtual void OnCollisionEndOverlap(std::shared_ptr<Actor> otherActor) override;
	virtual void Destroy() override;
	void Explode();



	
	int explosionRange; // controls the range of this bomb when it explodes

private:
	std::vector<std::shared_ptr<Explosion>> explosion;
	float timer;
	float initialTimer; //using to reset timer back to default value
}; 
