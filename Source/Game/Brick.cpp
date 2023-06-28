#include "Brick.h"
#include "Explosion.h"

void Brick::OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor)
{
	Actor::OnCollisionBeginOverlap(otherActor);

	std::shared_ptr<Explosion> enemy = std::dynamic_pointer_cast<Explosion>(otherActor);
	LOG(enemy);
	if (enemy)
	{
		SetActive(false);
	}
}