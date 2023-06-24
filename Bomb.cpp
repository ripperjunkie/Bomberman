#include "Bomb.h"
#include "Explosion.h"

#define DEFAULT_BOMB_RANGE 5

void Bomb::Start()
{
	Entity::Start();

	bStartTimer = true;
	timer = 2.f; //timer controls how long bomb will take to explode
	initialTimer = timer;
	explosionRange = 1;
}

void Bomb::Update()
{
	Entity::Update();


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

void Bomb::OnCollisionEndOverlap(Entity& other_actor)
{
	Entity::OnCollisionEndOverlap(other_actor);

	collision_type = ECollisionType::BLOCKING;
}

void Bomb::Destroy()
{
	Entity::Destroy();
}

void Bomb::Explode()
{
	//the reason why we have DEFAULT_BOMBS_RANGE, it's because we will always have 4 bombs to place around the first bomb
	//whereas the explosionRange will increase the amount of places that will be placed around 
	for (int i = 0; i < DEFAULT_BOMB_RANGE * explosionRange; i++)
	{
		explosion.push_back(*new Explosion(*level, ECollisionType::OVERLAP, EObjectMovType::MOVABLE, true, shared_sprite_sheet));
	}

	//I will figure out how to use the for here later on, it's not simple as it looks like
	explosion[0].get().SetLocation(collider.x, collider.y); //at the bomb location
	explosion[1].get().SetLocation(collider.x, collider.y + collider.height); //place on top of bomb
	explosion[2].get().SetLocation(collider.x + collider.width, collider.y); //place on right of bomb
	explosion[3].get().SetLocation(collider.x, collider.y - collider.height); //place on bottom of bomb
	explosion[4].get().SetLocation(collider.x - collider.width, collider.y); //place on left of bomb


	// destroy ourselves
	this->Destroy();
}