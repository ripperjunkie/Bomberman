#include "Enemy.h"

#include "Explosion.h"
#include "HealthComponent.h"



void Enemy::Start()
{
	Actor::Start();

	healthComp = std::make_shared<HealthComponent>(3);
	healthComp->SetHealthChangeCallback(std::bind(&Enemy::OnDie, this));
}

void Enemy::OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor)
{
	Actor::OnCollisionBeginOverlap(otherActor);

	if (std::shared_ptr<Explosion> enemy = std::dynamic_pointer_cast<Explosion>(otherActor))
	{
		if (healthComp)
		{
			healthComp->TakeDamage(1);
		}
	}
}


void Enemy::OnDie()
{
	SetActive(false);
}