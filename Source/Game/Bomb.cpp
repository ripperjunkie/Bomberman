#include "Bomb.h"
#include "Explosion.h"
#include "Engine/Managers/ActorManager.h"

#define DEFAULT_BOMB_RANGE 5

void Bomb::Start()
{
	Actor::Start();

	bStartTimer = true;
	timer = 2.f; //timer controls how long bomb will take to explode
	initialTimer = timer;
	explosionRange = 1;
}

void Bomb::Update()
{
	Actor::Update();



	//Destroy after a certain time if timer is active
	if (bStartTimer)
	{
		timer -= GetFrameTime();
		//printf("Timer: %f\n", timer);s

		if (timer <= 0.f)
		{
			Explode();
			bStartTimer = false;
			timer = initialTimer;
		}
	}
}

void Bomb::OnCollisionEndOverlap(Actor& other_actor)
{
	Actor::OnCollisionEndOverlap(other_actor);

	mCollisionType = ECollisionType::BLOCKING;
}

void Bomb::Destroy()
{
	Actor::Destroy();
}

void Bomb::Explode()
{
	std::vector<std::shared_ptr<Explosion>> explosion;
	//the reason why we have DEFAULT_BOMBS_RANGE, it's because we will always have 4 bombs to place around the first bomb
	//whereas the explosionRange will increase the amount of places that will be placed around 
	for (int i = 0; i < DEFAULT_BOMB_RANGE * explosionRange; i++)
	{
	//	explosion.push_back(*new Explosion(*level, ECollisionType::OVERLAP, EObjectMovType::MOVABLE, true, shared_sprite_sheet));
		explosion.push_back(ACTOR_MANAGER->SpawnActor<Explosion>());

	}



	//I will figure out how to use the for here later on, it's not simple as it looks like
	explosion[0]->SetLocation(mCollider.x, mCollider.y); //at the bomb location
	explosion[1]->SetLocation(mCollider.x, mCollider.y + mCollider.height); //place on top of bomb
	explosion[2]->SetLocation(mCollider.x + mCollider.width, mCollider.y); //place on right of bomb
	explosion[3]->SetLocation(mCollider.x, mCollider.y - mCollider.height); //place on bottom of bomb
	explosion[4]->SetLocation(mCollider.x - mCollider.width, mCollider.y); //place on left of bomb


	// destroy ourselves
	shared_from_this()->Destroy();
}