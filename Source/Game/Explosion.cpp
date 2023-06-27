#include "Explosion.h"
#include "Engine/Managers/ActorManager.h"



void Explosion::Start()
{
	Actor::Start();

	this->bStartTimer = true;
	this->timer = 1.f; 
	this->initialTimer = timer;

	// registering the overlap entities 
	for (int i = 0; i < ACTOR_MANAGER->GetInstance()->GetActors().size(); ++i)
	{
		if (ACTOR_MANAGER->GetInstance()->GetActors()[i].get() != this)
		{
			this->overlapped_entities.emplace(ACTOR_MANAGER->GetInstance()->GetActors()[i], false);
		}
	}
}

void Explosion::Update()
{
	Actor::Update();


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



void Explosion::Destroy()
{
	Actor::Destroy();
}
