#include "Explosion.h"


void Explosion::Start()
{
	Entity::Start();

	bStartTimer = true;
	timer = 15.f; 
	initialTimer = timer;
}

void Explosion::Update()
{
	Entity::Update();


	//Destroy after a certain time if timer is active
	if (bStartTimer)
	{
		timer -= GetFrameTime();
		//printf("Timer: %f\n", timer);

		if (timer <= 0.f)
		{
			bStartTimer = false;
			timer = initialTimer;
			Destroy();
		}
	}
}

void Explosion::OnCollisionBeginOverlap(Entity& other_actor)
{
	//TODO: 
	//Kill any entity overlapping this explosion
	//Destroy destroyable bricks

	//other_actor.SetActive(false);
}

void Explosion::Destroy()
{
	Entity::Destroy();

}
