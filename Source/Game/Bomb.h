#pragma once

#include "Engine/GameFramework/Actor.h"

class Bomb : public Actor
{
public:
	Bomb() : Actor()
	{
		CropSprite(224.f, 704.f);
		name = "bomb";
		Start();
	}

	virtual void Start() override;
	virtual void Update() override;
	virtual void OnCollisionEndOverlap(Actor& other_actor) override;
	virtual void Destroy() override;
	void Explode();



	std::shared_ptr<class Grid> tileMap = nullptr;
	std::vector<std::reference_wrapper<class Explosion>> explosion;
	int explosionRange; // controls the range of this bomb when it explodes
}; 
