#include "Explosion.h"
#include "Engine/Managers/ActorManager.h"



Explosion::Explosion() : Actor()
{
	mName = "explosion";
	mAnimationSpeed = 7.f;
	explosionAnim.push_back(RecCropLocation(324.f, 708.f));
	explosionAnim.push_back(RecCropLocation(352.f, 708.f));
	explosionAnim.push_back(RecCropLocation(384.f, 708.f));
	explosionAnim.push_back(RecCropLocation(418.f, 708.f));

	CropSprite(explosionAnim[0].x, explosionAnim[0].y);


	mAnimations.push_back(AnimationData(explosionAnim));
	mCollisionType = ECollisionType::OVERLAP;

}

void Explosion::Start()
{
	Actor::Start();

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
	if (bActive)
	{
		timer -= GetFrameTime();
		//printf("Timer: %f\n", timer);

		if (timer <= 0.f)
		{
			timer = initialTimer;
			Destroy();
		}
	}
}



void Explosion::Destroy()
{
	timer = initialTimer;
	Actor::Destroy();
}
