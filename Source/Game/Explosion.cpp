#include "Explosion.h"
#include "Engine/Managers/ActorManager.h"
#include "DamageInterface.h"
#include "Enemy.h"

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
	int debug = 0;
}

void Explosion::Update()
{
	Actor::Update();

	//for (auto& t : overlapped_entities)
	//{
	//	auto it = overlapped_entities.find(std::dynamic_pointer_cast<Enemy>( std::shared_ptr<Actor>(t.first)));
	//	if (it != overlapped_entities.end())
	//	{
	//		printf(it->second ?"true\n" : "false\n");
	//	}
	//}
	
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

void Explosion::OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor)
{
	Actor::OnCollisionBeginOverlap(otherActor);
	std::cout << __FUNCTION__ << std::endl;

	if (std::shared_ptr<IDamageInterface> damageInterface = std::dynamic_pointer_cast<IDamageInterface>(otherActor))
	{
		damageInterface->OnTakenDamage(&*otherActor, 1);
	}
}

void Explosion::OnCollisionEndOverlap(std::shared_ptr<Actor> otherActor)
{
	Actor::OnCollisionEndOverlap(otherActor);
}
