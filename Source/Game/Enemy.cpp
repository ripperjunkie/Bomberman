#include "Enemy.h"

#include "Bomb.h"
#include "Explosion.h"
#include "HealthComponent.h"
#include "Engine/Managers/ActorManager.h"


Enemy::Enemy() : Actor()
{
	idle.push_back(RecCropLocation(0, 384));
	mAnimations.push_back(AnimationData(idle));
	CropSprite(idle[0].x, idle[0].y);
}

void Enemy::Start()
{
	Actor::Start();

	healthComp = std::make_shared<HealthComponent>(3);
	healthComp->SetHealthChangeCallback(std::bind(&Enemy::OnDie, this));

	// let's reserve the bomb to use later
	//bomb = ACTOR_MANAGER->SpawnActor<Bomb>();
}

void Enemy::Update()
{
	Actor::Update();

	{
		std::string hp = "HP: " + std::to_string(healthComp->GetCurrentHP());
		DrawText(hp.c_str(), 0, 25, 24, YELLOW);
	}

	if (bStartTimer)
	{
		timer -= GetFrameTime();
		//printf("Timer: %f\n", timer);

		if (timer <= 0.f)
		{
			timer = initialTimer;
			bCanPlaceBomb = true;
		}
	}
}

void Enemy::OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor)
{
	Actor::OnCollisionBeginOverlap(otherActor);

}


void Enemy::OnDie()
{
	SetActive(false);
}



/***************** INTERFACES ***********************/
void Enemy::OnTakenDamage(Actor* damageCauser, int damageAmount)
{
	std::cout << __FUNCTION__ << std::endl;


	if (!damageCauser)
		return;

	if (healthComp)
	{
		healthComp->TakeDamage(damageAmount);
	}
}