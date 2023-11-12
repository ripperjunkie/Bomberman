#include "Bomb.h"
#include "Explosion.h"
#include "Engine/Managers/ActorManager.h"

#define DEFAULT_BOMB_RANGE 5

Bomb::Bomb() : Actor()
{
	CropSprite(224.f, 704.f);
	mName = "bomb";
	mCollisionType = ECollisionType::OVERLAP;
	mObjectMovementType = EObjectMovType::MOVABLE;
}

void Bomb::Start()
{
	Actor::Start();

	timer = 3.f; //timer controls how long bomb will take to explode
	initialTimer = timer;
	explosionRange = 1;
	bActive = false;

	for (int i = 0; i < DEFAULT_BOMB_RANGE * explosionRange; i++)
	{
		explosion.push_back(ACTOR_MANAGER->SpawnActor<Explosion>());
	}

}

void Bomb::Update()
{
	Actor::Update();

	//Destroy after a certain time if timer is active
	if (bActive)
	{
		timer -= GetFrameTime();
		//printf("Timer: %f\n", timer);s

		if (timer <= 0.f)
		{
			Explode();
			timer = initialTimer;
		}
	}
}

void Bomb::OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor)
{
	Actor::OnCollisionBeginOverlap(otherActor);

	//if (otherActor)
	//printf("\n Collision begin overlap from: %s, to: %s\n", this->mName.c_str(), otherActor->mName.c_str());
	LOG("OnCollisionBeginOverlap");

}

void Bomb::OnCollisionEndOverlap(Actor& otherActor)
{
	Actor::OnCollisionEndOverlap(otherActor);

	mCollisionType = ECollisionType::BLOCKING;
}

void Bomb::Destroy()
{
	timer = initialTimer;
	mCollisionType = ECollisionType::IGNORE;
	Actor::Destroy();
}

void Bomb::Explode()
{
	std::cout << "Explode\n";

	//the reason why we have DEFAULT_BOMBS_RANGE, it's because we will always have 4 bombs to place around the first bomb
	//whereas the explosionRange will increase the amount of places that will be placed around 
	for (int i = 0; i < DEFAULT_BOMB_RANGE * explosionRange; i++)
	{
		explosion[i]->SetActive(true);
	}

	// TODO: We can make a vector with the location for each collision so that we can iterate it through a for loop instead of hard coding it...
	explosion[0]->SetLocation(mCollider.x, mCollider.y); //at the bomb location
	explosion[1]->SetLocation(mCollider.x, mCollider.y + mCollider.height); //place on top of bomb
	explosion[2]->SetLocation(mCollider.x + mCollider.width, mCollider.y); //place on right of bomb
	explosion[3]->SetLocation(mCollider.x, mCollider.y - mCollider.height); //place on bottom of bomb
	explosion[4]->SetLocation(mCollider.x - mCollider.width, mCollider.y); //place on left of bomb


	// destroy ourselves
	shared_from_this()->Destroy();
}